#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "mf.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <ctype.h>
#include <errno.h>
//MAX_MESSAGE_QUEUES???
#define MAX_PROCESSES 16
#define MAX_SEMAPHORE_NAME_LEN 255
#define MAX_MESSAGE_QUEUES 32
#define MAX_HOLE_COUNT 32

#define KB_TO_BYTES 1024
#define MIN_MQSIZE_BYTES (MIN_MQSIZE * KB_TO_BYTES) // Assuming MIN_MQSIZE is in KB

// General-purpose semaphore name
#define GENERAL_SEM_NAME "/mf_general_semaphore"
#define DEFAULTMQNAME "/defaultmqname"
#define DEFAULTMQSEM_NAME "/mf_mq_semaphore"
#define DEFAULTSPACESEM_NAME "/mf_space_semaphore"
#define DEFAULTCOUNTSEM_NAME "/mf_count_semaphore"

typedef struct {
    size_t start_index;  // Start of the free block
    size_t size;         // Size of the free block
} FreeBlock;

typedef struct {
    char mq_name[MAX_MQNAMESIZE];
    size_t mq_size;          // Total size available for the message queue
    unsigned int mq_id;      // Unique identifier for the message queue
    size_t in_index;         // Index for the next write position in the message queue
    size_t out_index;        // Index for the next read position from the message queue
    int start_index;         // Index for the start of the message queue
    int num_messages;        // Number of messages in the queue
    unsigned int ref_count;  // Reference count for the message queue
    char sem_mq[MAX_SEMAPHORE_NAME_LEN];
    char sem_space[MAX_SEMAPHORE_NAME_LEN];
    char sem_count[MAX_SEMAPHORE_NAME_LEN];
} MessageQueueHeader;

typedef struct {
    size_t size;
    char data[];  // Flexible array member for the message's data
} Message;

typedef struct {
    pid_t pids[MAX_PROCESSES]; 
    int num_active_processes; 
    int num_active_queues;
    MessageQueueHeader queue_headers[MAX_MESSAGE_QUEUES];  // Array to hold message queue headers
    FreeBlock freeBlocks[MAX_HOLE_COUNT];
    int num_free_blocks;  // Number of active free blocks
} MFSharedData;

int shm_fd = -1;
char shmem_name[MAXFILENAME];
MFSharedData *mf_sharedData = NULL;

size_t shmem_size_kb, max_msgs_in_queue, MAX_QUEUES_IN_SHMEM;

// Global variable for the general semaphore
sem_t *general_sem;

// Function to trim leading and trailing spaces
char* trimWhitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0) {  // All spaces?
        return str;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

void readConfig(const char *filename, char *shmem_name, size_t *shmem_size_kb, size_t *max_msgs_in_queue, size_t *max_queues_in_shmem) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the configuration file");
        exit(EXIT_FAILURE);
    }

    char line[256]; // Assuming no line exceeds 255 characters
    while (fgets(line, sizeof(line), file)) {
        // Ignore comments
        if (line[0] == '#') continue;

        // Process valid lines
        char key[256], value[256];
        if (sscanf(line, "%255s \"%255[^\"]\"", key, value) == 2 || sscanf(line, "%255s %255s", key, value) == 2) {
            // The above tries to read values both with and without quotes.
            char *val = value;
            val = trimWhitespace(val); // Trim whitespace

            if (strcmp(key, "SHMEM_NAME") == 0) {
                strncpy(shmem_name, val, MAXFILENAME - 1);
                shmem_name[MAXFILENAME - 1] = '\0'; // Ensure null-terminated
            } else if (strcmp(key, "SHMEM_SIZE") == 0) {
                *shmem_size_kb = strtoul(val, NULL, 10);
            } else if (strcmp(key, "MAX_MSGS_IN_QUEUE") == 0) {
                *max_msgs_in_queue = strtoul(val, NULL, 10);
            } else if (strcmp(key, "MAX_QUEUES_IN_SHMEM") == 0) {
                *max_queues_in_shmem = strtoul(val, NULL, 10);
            }
        }
    }
    fclose(file);
}

void initialize_memory() {
    mf_sharedData->freeBlocks[0].start_index = sizeof(MFSharedData);
    mf_sharedData->freeBlocks[0].size = shmem_size_kb * KB_TO_BYTES - sizeof(MFSharedData);
    mf_sharedData->num_free_blocks = 1;
}

int allocate_space(size_t size) {
    for (int i = 0; i < mf_sharedData->num_free_blocks; i++) {
        if (mf_sharedData->freeBlocks[i].size >= size) {
            size_t alloc_start = mf_sharedData->freeBlocks[i].start_index;
            mf_sharedData->freeBlocks[i].start_index += size;
            mf_sharedData->freeBlocks[i].size -= size;
            if (mf_sharedData->freeBlocks[i].size == 0) {
                // Remove the block by shifting left
                for (int j = i; j < mf_sharedData->num_free_blocks - 1; j++) {
                    mf_sharedData->freeBlocks[j] = mf_sharedData->freeBlocks[j + 1];
                }
                mf_sharedData->num_free_blocks--;
            }
            return alloc_start;
        }
    }
    return -1;  // No suitable space found
}

void deallocate_space(size_t start_index, size_t size) {
    if (mf_sharedData->num_free_blocks >= MAX_HOLE_COUNT) {
        fprintf(stderr, "No room to deallocate space, maximum holes exceeded.\n");
        return;
    }

    // Insert the new free block in sorted order based on start_index
    int i;
    for (i = 0; i < mf_sharedData->num_free_blocks; i++) {
        if (mf_sharedData->freeBlocks[i].start_index > start_index) {
            break;
        }
    }

    // Shift elements to the right to make space for the new block
    for (int j = mf_sharedData->num_free_blocks; j > i; j--) {
        mf_sharedData->freeBlocks[j] = mf_sharedData->freeBlocks[j - 1];
    }

    mf_sharedData->freeBlocks[i].start_index = start_index;
    mf_sharedData->freeBlocks[i].size = size;
    mf_sharedData->num_free_blocks++;

    // Now check and merge adjacent free blocks if possible
    for (int k = 0; k < mf_sharedData->num_free_blocks - 1; k++) {
        size_t end_index = mf_sharedData->freeBlocks[k].start_index + mf_sharedData->freeBlocks[k].size;

        if (end_index == mf_sharedData->freeBlocks[k + 1].start_index) {
            // Merge blocks k and k+1
            mf_sharedData->freeBlocks[k].size += mf_sharedData->freeBlocks[k + 1].size;
            
            // Shift remaining blocks left
            for (int l = k + 1; l < mf_sharedData->num_free_blocks - 1; l++) {
                mf_sharedData->freeBlocks[l] = mf_sharedData->freeBlocks[l + 1];
            }

            mf_sharedData->num_free_blocks--;
            k--; // Check the new k again in case it also merges with the next one
        }
    }
}

int mf_init() {
    
    
    readConfig(CONFIG_FILENAME, shmem_name, &shmem_size_kb, &max_msgs_in_queue, &MAX_QUEUES_IN_SHMEM);
    printf("Max messages in queue: %lu\n", max_msgs_in_queue);
    size_t shmem_size = shmem_size_kb * KB_TO_BYTES;
    size_t max_queues_possible = shmem_size / MIN_MQSIZE_BYTES;
    size_t min = (MAX_QUEUES_IN_SHMEM < max_queues_possible) ? MAX_QUEUES_IN_SHMEM : max_queues_possible;
    MAX_QUEUES_IN_SHMEM = min;

    shm_fd = shm_open(shmem_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return -1;
    }

    if (ftruncate(shm_fd, shmem_size) == -1) {
        perror("ftruncate failed");
        close(shm_fd);
        return -1;
    }

    mf_sharedData = mmap(NULL, shmem_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (mf_sharedData == MAP_FAILED) {
        perror("mmap failed");
        close(shm_fd);
        return -1;
    }

    close(shm_fd);

    general_sem = sem_open(GENERAL_SEM_NAME, O_CREAT | O_RDWR, 0666, 1);
    if (general_sem == SEM_FAILED) {
        perror("Failed to create the general semaphore");
        munmap(mf_sharedData, sizeof(MFSharedData));
        close(shm_fd);
        return -1;
    }

    memset(mf_sharedData, 0, shmem_size);
    mf_sharedData->num_active_queues = 0;

    for (size_t i = 0; i < min; ++i) {
        mf_sharedData->queue_headers[i].mq_id = i;
        mf_sharedData->queue_headers[i].mq_size = 0;
        mf_sharedData->queue_headers[i].ref_count = 0;
        mf_sharedData->queue_headers[i].start_index = 0;
        mf_sharedData->queue_headers[i].num_messages = 0;
        mf_sharedData->queue_headers[i].in_index = 0;
        mf_sharedData->queue_headers[i].out_index = 0;
        snprintf(mf_sharedData->queue_headers[i].mq_name, sizeof(mf_sharedData->queue_headers[i].mq_name), "%s", DEFAULTMQNAME);
        snprintf(mf_sharedData->queue_headers[i].sem_mq, sizeof(mf_sharedData->queue_headers[i].sem_mq), "%s_%lu", DEFAULTMQSEM_NAME, i);
        snprintf(mf_sharedData->queue_headers[i].sem_space, sizeof(mf_sharedData->queue_headers[i].sem_space), "%s_%lu", DEFAULTSPACESEM_NAME, i);
        snprintf(mf_sharedData->queue_headers[i].sem_count, sizeof(mf_sharedData->queue_headers[i].sem_count), "%s_%lu", DEFAULTCOUNTSEM_NAME, i);
    }

    initialize_memory();
    return 0;
}

int mf_destroy() {
    printf("Destroying message facility.\n");

    // Check if the shared memory is initialized
    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized.\n");
        return -1;
    }

    // Unlink all semaphores associated with the message queues
    for (int i = 0; i < MAX_QUEUES_IN_SHMEM; i++) {
        if (mf_sharedData->queue_headers[i].mq_size > 0) {  // If the queue was used
            sem_unlink(mf_sharedData->queue_headers[i].sem_mq);
            sem_unlink(mf_sharedData->queue_headers[i].sem_space);
            sem_unlink(mf_sharedData->queue_headers[i].sem_count);
        }
    }

    // Unlink and close the general semaphore
    if (general_sem != SEM_FAILED) {
        sem_close(general_sem);
        sem_unlink(GENERAL_SEM_NAME);
    }

    // Unmap and close the shared memory
    if (mf_sharedData != MAP_FAILED) {
        munmap(mf_sharedData, shmem_size_kb * KB_TO_BYTES);
    }

    if (shm_fd != -1) {
        close(shm_fd);
        shm_unlink(shmem_name);
    }

    printf("Message facility destroyed successfully.\n");
    return 0;
}

int mf_connect() {
    printf("In mf_connect, pid: %d\n", getpid());
    // If the shared memory is not yet mapped (for instance, after program restart), map it
    if (mf_sharedData == NULL) {
        readConfig(CONFIG_FILENAME, shmem_name, &shmem_size_kb, &max_msgs_in_queue, &MAX_QUEUES_IN_SHMEM);

        shm_fd = shm_open(shmem_name, O_RDWR, 0666);

        if (shm_fd == -1) {
            perror("Failed to open shared memory in mf_connect");
            return -1;
        }
        size_t shmem_size = shmem_size_kb * KB_TO_BYTES;

        // Map the shared memory object
        mf_sharedData = mmap(NULL, shmem_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (mf_sharedData == MAP_FAILED) {
            perror("Failed to map shared memory in mf_connect");
            close(shm_fd);
            return -1;
        }

        general_sem = sem_open(GENERAL_SEM_NAME, O_CREAT | O_RDWR, 0666, 1);
        if (general_sem == SEM_FAILED) {
            perror("Failed to create the general semaphore in mf_connect");
            munmap(mf_sharedData, sizeof(MFSharedData));
            close(shm_fd);
            return -1;
        }
    }
    // Safely increment the number of active processes
    sem_wait(general_sem); // Lock the general semaphore to safely update shared data

    // Check if there is space for a new process
    if (mf_sharedData->num_active_processes >= MAX_PROCESSES) {
        sem_post(general_sem); // Release semaphore before returning
        fprintf(stderr, "Maximum number of processes reached in mf_connect\n");
        return -1; // Return an error if no space
    }

    // Register the new process
    mf_sharedData->pids[mf_sharedData->num_active_processes] = getpid();
    mf_sharedData->num_active_processes++;
    printf("Connected process with PID: %d and num_active_processes: %d\n", getpid(), mf_sharedData->num_active_processes);

    sem_post(general_sem); // Release the general semaphore
    printf("Exiting from mf_connect()\n\n");
    return 0; // Return success
}
   
int mf_disconnect() {
    printf("In mf_disconnect, pid: %d\n", getpid());

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not mapped; cannot disconnect.\n");
        return -1;
    }

    // Lock the general semaphore to safely update shared data
    sem_wait(general_sem);

    pid_t pid = getpid();
    int found = 0;

    // Find the PID in the array and remove it
    for (int i = 0; i < mf_sharedData->num_active_processes; i++) {
        if (mf_sharedData->pids[i] == pid) {
            found = 1;
            // Shift all subsequent PIDs down to fill the gap
            for (int j = i; j < mf_sharedData->num_active_processes - 1; j++) {
                mf_sharedData->pids[j] = mf_sharedData->pids[j + 1];
            }
            mf_sharedData->num_active_processes--;
            break;
        }
    }

    if (!found) {
        fprintf(stderr, "PID not found in active processes in mf_disconnect().\n");
        sem_post(general_sem); // Release semaphore before returning
        return -1; // PID not found
    }

    sem_post(general_sem); // Release the general semaphore
    printf("Exiting from mf_disconnect()\n\n");

    return 0; // Successfully disconnected
}

int mf_create(char *mqname, int mqsize) {
    printf("In mf_create, pid: %d\n", getpid());

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_create().\n");
        return -1;
    }
    mqsize *= KB_TO_BYTES; // Convert to bytes
    if (mqsize <= 0 || mqsize < MIN_MQSIZE_BYTES) {
        fprintf(stderr, "Invalid queue size. It must be at least %d bytes in mf_create().\n", MIN_MQSIZE_BYTES);
        return -1;
    }

    // Check for unique queue name
    sem_wait(general_sem); // Lock the general semaphore to safely check queue names
    for (int j = 0; j < MAX_QUEUES_IN_SHMEM; j++) {
        if (mf_sharedData->queue_headers[j].mq_size != 0 && strcmp(mf_sharedData->queue_headers[j].mq_name, mqname) == 0) {
            sem_post(general_sem);
            fprintf(stderr, "Message queue with name '%s' already exists in mf_create().\n", mqname);
            return -1; // Queue name already exists
        }
    }

    // Check if there is space for a new message queue
    if (mf_sharedData->num_active_queues >= MAX_QUEUES_IN_SHMEM) {
        sem_post(general_sem); // Release semaphore before returning
        fprintf(stderr, "Maximum number of message queues reached in mf_create().\n");
        return -1; // No space for more queues
    }

    // Find an available slot for the new message queue
    for (int i = 0; i < MAX_QUEUES_IN_SHMEM; i++) {
        if (mf_sharedData->queue_headers[i].mq_size == 0) { // Indicates available slot

            int hole_start = allocate_space(mqsize);
            if (hole_start == -1) {
                fprintf(stderr, "No hole found for the new message queue.\n");
                sem_post(general_sem);
                return -1; // No space available
            }
            strncpy(mf_sharedData->queue_headers[i].mq_name, mqname, MAX_MQNAMESIZE - 1);
            mf_sharedData->queue_headers[i].mq_name[MAX_MQNAMESIZE - 1] = '\0'; // Ensure null termination
            mf_sharedData->queue_headers[i].mq_id = i; // Assign unique queue identifier
            mf_sharedData->queue_headers[i].mq_size = mqsize;
            mf_sharedData->queue_headers[i].start_index = hole_start;
            mf_sharedData->queue_headers[i].in_index = 0;
            mf_sharedData->queue_headers[i].out_index = 0;
            mf_sharedData->queue_headers[i].ref_count = 0; // Start with one reference
            mf_sharedData->queue_headers[i].num_messages = 0; // No messages yet
            
            // Create the semaphore for this queue
            sem_t *mq_sem = sem_open(mf_sharedData->queue_headers[i].sem_mq, O_CREAT, 0666, 1);
            sem_t *space_sem = sem_open(mf_sharedData->queue_headers[i].sem_space, O_CREAT, 0666, max_msgs_in_queue);
            sem_t *count_sem = sem_open(mf_sharedData->queue_headers[i].sem_count, O_CREAT, 0666, 0);

            if (mq_sem == SEM_FAILED || space_sem == SEM_FAILED || count_sem == SEM_FAILED) {
                fprintf(stderr, "Failed to open semaphores.\n");
                sem_post(general_sem);
                return -1;
            }

            mf_sharedData->num_active_queues++;
            sem_post(general_sem); // Release the general semaphore
            printf("Exiting from mf_create() with success!\n\n");
            return 0; // Success
        }
    }

    sem_post(general_sem); // Release the general semaphore
    printf("Exiting from mf_create() with error!\n\n");
    return -1; // No available slot found
}

int mf_remove(char *mqname) {
    printf("In mf_remove, pid: %d\n", getpid());

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_remove().\n");
        return -1;
    }

    // Lock the general semaphore to safely modify shared data
    sem_wait(general_sem);

    // Search for the queue by name
    for (int i = 0; i < MAX_QUEUES_IN_SHMEM; i++) {
        if (mf_sharedData->queue_headers[i].mq_size != 0 && 
            strcmp(mf_sharedData->queue_headers[i].mq_name, mqname) == 0) {
            
            // Check if the reference count is zero
            if (mf_sharedData->queue_headers[i].ref_count > 0) {
                sem_post(general_sem);
                fprintf(stderr, "Cannot remove queue '%s': Reference count is not zero in mf_remove().\n", mqname);
                return -1;
            }

            sem_t *sem_mq = sem_open(mf_sharedData->queue_headers[i].sem_mq, 0);
            if (sem_mq != SEM_FAILED) {
                sem_close(sem_mq);
                sem_unlink(mf_sharedData->queue_headers[i].sem_mq);
            }

            sem_t *sem_space = sem_open(mf_sharedData->queue_headers[i].sem_space, max_msgs_in_queue);
            if (sem_space != SEM_FAILED) {
                sem_close(sem_space);
                sem_unlink(mf_sharedData->queue_headers[i].sem_space);
            }

            sem_t *sem_count = sem_open(mf_sharedData->queue_headers[i].sem_count, 0);
            if (sem_count != SEM_FAILED) {
                sem_close(sem_count);
                sem_unlink(mf_sharedData->queue_headers[i].sem_count);
            }

            // Clear the queue header data
            memset(&mf_sharedData->queue_headers[i], 0, sizeof(MessageQueueHeader));
            mf_sharedData->queue_headers[i].mq_id = i;
            mf_sharedData->queue_headers[i].mq_size = 0;
            mf_sharedData->queue_headers[i].ref_count = 0;
            mf_sharedData->queue_headers[i].num_messages = 0;
            mf_sharedData->queue_headers[i].in_index = 0;
            mf_sharedData->queue_headers[i].out_index = 0;
            snprintf(mf_sharedData->queue_headers[i].mq_name, sizeof(mf_sharedData->queue_headers[i].mq_name), "%s", DEFAULTMQNAME);
            snprintf(mf_sharedData->queue_headers[i].sem_mq, sizeof(mf_sharedData->queue_headers[i].sem_mq), "%s_%d", DEFAULTMQSEM_NAME, i);
            snprintf(mf_sharedData->queue_headers[i].sem_space, sizeof(mf_sharedData->queue_headers[i].sem_space), "%s_%d", DEFAULTSPACESEM_NAME, i);
            snprintf(mf_sharedData->queue_headers[i].sem_count, sizeof(mf_sharedData->queue_headers[i].sem_count), "%s_%d", DEFAULTCOUNTSEM_NAME, i);

            mf_sharedData->num_active_queues--;
            deallocate_space(mf_sharedData->queue_headers[i].start_index, mf_sharedData->queue_headers[i].mq_size);
            sem_post(general_sem);
            printf("Exiting from mf_remove() with success!\n\n");
            return 0; // Successfully removed
        }
    }

    sem_post(general_sem);
    fprintf(stderr, "Queue '%s' not found in mf_remove()\n", mqname);
    printf("Exiting from mf_remove() with error!\n\n");
    return -1; // Queue not found
}

int mf_open(char *mqname) {
    printf("In mf_open, pid: %d\n", getpid());

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_open().\n");
        return -1;
    }

    sem_wait(general_sem); // Lock the general semaphore to safely read shared data

    for (int i = 0; i < MAX_QUEUES_IN_SHMEM; i++) {
        if (mf_sharedData->queue_headers[i].mq_size != 0 && strcmp(mf_sharedData->queue_headers[i].mq_name, mqname) == 0) {
            mf_sharedData->queue_headers[i].ref_count++; // Increment the reference count
            sem_post(general_sem);
            printf("Exiting from mf_open() with success! pid: %d\n\n", getpid());
            return mf_sharedData->queue_headers[i].mq_id; // Return the queue ID
        }
    }

    sem_post(general_sem);
    fprintf(stderr, "Queue '%s' not found in mf_open().\n", mqname);
    printf("Exiting from mf_open() with error!\n\n");
    return -1; // Queue not found
}

int mf_close(int qid) {
    printf("In mf_close, pid: %d\n", getpid());

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_close().\n");
        return -1;
    }

    if (qid < 0 || qid >= MAX_QUEUES_IN_SHMEM) {
        fprintf(stderr, "Invalid queue ID in mf_close().\n");
        return -1;
    }

    sem_wait(general_sem); // Lock the general semaphore to safely modify shared data
    printf("Queue ID: %d\n", qid);
    if (mf_sharedData->queue_headers[qid].mq_size == 0) {
        sem_post(general_sem);
        fprintf(stderr, "Queue ID %d is not active in mf_close().\n", qid);
        return -1;
    }

    if (mf_sharedData->queue_headers[qid].ref_count > 0) {
        mf_sharedData->queue_headers[qid].ref_count--; // Decrement the reference count
        sem_post(general_sem);
        printf("Exiting from mf_close() with success! pid: %d\n\n", getpid());
        return 0; // Successfully decremented the reference count
    }

    sem_post(general_sem);
    fprintf(stderr, "Queue ID %d cannot be closed as it is already closed.\n", qid);
    printf("Exiting from mf_close() with error!\n\n");
    return -1; // Reference count is already zero, cannot close
}

int mf_send(int qid, void *bufptr, int datalen) {
    printf("In mf_send, pid: %d qid: %d\n", getpid(), qid);

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_send().\n");
        return -1;
    }

    if (bufptr == NULL || datalen < MIN_DATALEN || datalen > MAX_DATALEN) {
        fprintf(stderr, "Invalid buffer pointer or data length in mf_send().\n");
        return -1;
    }

    if (qid < 0 || qid >= MAX_QUEUES_IN_SHMEM) {
        fprintf(stderr, "Invalid queue ID in mf_send().\n");
        return -1;
    }

    MessageQueueHeader *queue = &mf_sharedData->queue_headers[qid];
    if (queue->mq_size == 0) {
        printf("Message queue is not active.\n");
        return -1;
    }

    sem_t *sem_mq = sem_open(queue->sem_mq, 0);
    sem_t *sem_space = sem_open(queue->sem_space, 0);
    sem_t *sem_count = sem_open(queue->sem_count, 0);
    if (sem_mq == SEM_FAILED || sem_space == SEM_FAILED || sem_count == SEM_FAILED) {
        perror("Failed to open semaphore in mf_send()");
        return -1;
    }
    
    sem_wait(sem_space); // Wait until space is available
    
    sem_wait(sem_mq); // Lock the queue access
    
    // Calculate total size needed for the message including the Message struct overhead
    size_t total_size = sizeof(Message) + datalen;
    int available_space = queue->out_index <= queue->in_index ?
                          queue->mq_size - (queue->in_index - queue->out_index) : 
                          queue->out_index - queue->in_index - 1;

    // Wait until there is space
    while (available_space < total_size) {
        
        sem_post(sem_mq); // Unlock the queue before sleeping
        sem_post(sem_space); // Unlock the space semaphore before sleeping
        usleep(1000); // Wait until space is available
        sem_wait(sem_mq); // Lock the queue again after waking up
        sem_wait(sem_space); // Lock the space semaphore again after waking up
        available_space = queue->out_index <= queue->in_index ?
                          queue->mq_size - (queue->in_index - queue->out_index) : 
                          queue->out_index - queue->in_index - 1;
    }
    
    // Handle message wrapping in the buffer
    char *queue_data_start = (char*)mf_sharedData + sizeof(MFSharedData) + queue->start_index;  // Assuming MFSharedData struct precedes the actual message queue data in shared memory.
    
    Message *msg = (Message *)(queue_data_start + queue->in_index);
    msg->size = datalen;    

    if (queue->mq_size - queue->in_index >= total_size) {
        // If the message fits before wrapping, simply copy it in one go
        memcpy(msg->data, bufptr, datalen);
        queue->in_index = (queue->in_index + total_size) % queue->mq_size;
    } else {
        // If the message does not fit without wrapping, split it into two parts
        int first_part_size = queue->mq_size - queue->in_index;
        memcpy(msg->data, bufptr, first_part_size);  // Copy the first part till the end of the queue buffer
        memcpy(queue_data_start, (char*)bufptr + first_part_size, datalen - first_part_size);  // Start from the beginning of the queue buffer for the rest
        queue->in_index = total_size - first_part_size;  // Set the new input index to the size of the second part
    }

    queue->num_messages++; // Increment the count of messages
    
    sem_post(sem_mq);
    sem_post(sem_count); // Signal other waiting processes if any

    //sem_post(sem_space); // Signal other waiting processes if any

    sem_close(sem_mq);
    sem_close(sem_space);
    sem_close(sem_count);
    
    printf("Exiting from mf_send() with success! pid: %d\n", getpid());
    return 0;
}

int mf_recv(int qid, void *bufptr, int bufsize) {
    printf("In mf_recv, pid: %d qid: %d\n", getpid(), qid);

    if (mf_sharedData == NULL) {
        fprintf(stderr, "Shared memory is not initialized in mf_recv().\n");
        return -1;
    }

    if (bufptr == NULL || bufsize < MIN_DATALEN) {
        fprintf(stderr, "Invalid buffer pointer or buffer size is too small in mf_recv().\n");
        return -1;
    }

    if (qid < 0 || qid >= MAX_QUEUES_IN_SHMEM || mf_sharedData->queue_headers[qid].mq_size == 0) {
        fprintf(stderr, "Invalid queue ID or queue not active in mf_recv().\n");
        return -1;
    }
    MessageQueueHeader *queue = &mf_sharedData->queue_headers[qid];
    sem_t *sem_mq = sem_open(queue->sem_mq, 0);
    sem_t *sem_space = sem_open(queue->sem_space, 0);
    sem_t *sem_count = sem_open(queue->sem_count, 0);

    if (sem_mq == SEM_FAILED || sem_space == SEM_FAILED) {
        perror("Failed to open semaphore in mf_recv()");
        return -1;
    }

    
    sem_wait(sem_count); // Wait until there is a message to receive
    
    sem_wait(sem_mq); // Lock the queue access
    

    char *queue_data_start = (char*)mf_sharedData + sizeof(MFSharedData) + queue->start_index;
    
    Message *msg = (Message *)(queue_data_start + queue->out_index);
    int message_size = msg->size;

    if (bufsize < message_size) { // MAYBE BUG IS HERE!
        fprintf(stderr, "Buffer size too small for the message in mf_recv().\n");
        size_t total_size = sizeof(Message) + message_size;
        queue->out_index = (queue->out_index + total_size) % queue->mq_size;
        queue->num_messages--;
        sem_post(sem_mq);
        return -1;
    }

    size_t first_part_size;
    if (queue->out_index + sizeof(Message) + message_size <= queue->mq_size) {
        // If the message does not wrap around the buffer
        memcpy(bufptr, msg->data, message_size);
    } else {
        // If the message wraps around the buffer
        first_part_size = queue->mq_size - queue->out_index;
        memcpy(bufptr, msg->data, first_part_size);
        memcpy((char *)bufptr + first_part_size, queue_data_start, message_size - first_part_size);
    }

    size_t total_size = sizeof(Message) + message_size;
    queue->out_index = (queue->out_index + total_size) % queue->mq_size;
    queue->num_messages--;

    sem_post(sem_mq);
    sem_post(sem_space);

    sem_close(sem_mq);
    sem_close(sem_space);
    sem_close(sem_count);
    
    printf("Exiting from mf_recv() with success! pid: %d\n", getpid());
    return message_size;
}

int mf_print() {
    if (mf_sharedData == NULL) {
        printf("Shared memory is not initialized.\n");
        return -1;
    }

    printf("Shared Memory Overview:\n");
    printf("Total number of active processes: %d\n", mf_sharedData->num_active_processes);
    printf("Total number of active message queues: %d\n", mf_sharedData->num_active_queues);

    for (int i = 0; i < MAX_QUEUES_IN_SHMEM; i++) {
        MessageQueueHeader *queue = &mf_sharedData->queue_headers[i];
        if (queue->mq_size > 0) {  // Only print details for initialized queues
            printf("\nQueue ID %d:\n", queue->mq_id);
            printf("  Queue Name: %s\n", queue->mq_name);
            printf("  Queue Size: %zu bytes\n", queue->mq_size);
            printf("  In Index: %zu (write position)\n", queue->in_index);
            printf("  Out Index: %zu (read position)\n", queue->out_index);
            printf("  Number of Messages: %d\n", queue->num_messages);
            printf("  Reference Count: %u\n", queue->ref_count);
            printf("  Semaphore for Queue Access: %s\n", queue->sem_mq);
            printf("  Semaphore for Space Availability: %s\n", queue->sem_space);
            printf("  Semaphore for Message Count Availability: %s\n", queue->sem_count);
        }
    }
    printf("Holes (Free Spaces):\n");
    for (int i = 0; i < mf_sharedData->num_free_blocks; i++) {
        printf("Hole %d: Start Offset: %ld, Size: %ld bytes\n",
               i, mf_sharedData->freeBlocks[i].start_index, mf_sharedData->freeBlocks[i].size);
    }

    return 0;
}