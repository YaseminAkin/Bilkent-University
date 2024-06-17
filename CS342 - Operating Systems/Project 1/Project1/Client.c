#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>           
#include <sys/stat.h> 

#include "message.h"
#include <signal.h>

void client_signal_handler(int sig) {
    if (sig == SIGTERM) {
        exit(0);
    }
}

int main(int argc, char const *argv[]) {

    signal(SIGTERM, client_signal_handler);

    // Handle and initialize user input arguments
    if (argc < 2) { // Ensure at least MQNAME is provided
        fprintf(stderr, "Usage: %s MQNAME [-b COMFILE] [-s WSIZE]\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char* mqName = argv[1]; // The first argument is MQNAME
    const char* file_path = NULL;
    int wsize = 1;
    // Start from index 2 because MQNAME is at index 1
    for (int i = 2; i < argc; i++) {  
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {  
            wsize = atoi(argv[i + 1]);
            i++; // Skip next argument as it's already processed
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {  
            file_path = argv[i + 1];  
            i++; // Skip next argument as it's already processed  
        }
    }
    // Validate wsize  
    if (wsize <= 0) {
        fprintf(stderr, "Error: -s <WSIZE> must be a positive integer.\n");  
        return EXIT_FAILURE;
    }

    // Name pipes uniquely by using pids
    int client_id = getpid(); // Use the process ID as the client ID
    // Names for the client-to-server and server-to-client pipes
    char cs_pipe[100], sc_pipe[100];
    sprintf(cs_pipe, "/tmp/cs_pipe_%d", client_id);
    sprintf(sc_pipe, "/tmp/sc_pipe_%d", client_id);

    mqd_t mq;
    // Open the message queue for both reading and writing
    mq = mq_open(mqName, O_RDWR, 0644, NULL);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Creating named pipes (FIFOs)
    if (mkfifo(cs_pipe, 0666) == -1) {
        perror("mkfifo CS_PIPE failed");
        exit(1);
    }
    if (mkfifo(sc_pipe, 0666) == -1) {
        perror("mkfifo SC_PIPE failed");
        exit(1);
    }

    // Prepare and send CONREQUEST message
    char dataContent[BUFFER_SIZE];
    int dataLength = snprintf(dataContent, BUFFER_SIZE, "%d %s %s %d", client_id, cs_pipe, sc_pipe, wsize);
    // Calculate total message size (length + type + padding + data)
    uint32_t totalSize = 4 + 1 + 3 + dataLength; // Header size + data length
    uint32_t totalSizeLE = htole32(totalSize); // Convert total size to little endian
    // Allocate buffer for the entire message
    char* message = malloc(totalSize);
    if (!message) {
        perror("Failed to allocate memory for message");
        exit(EXIT_FAILURE);
    }
    // Fill in the message buffer
    memcpy(message, &totalSizeLE, 4); // Total size
    message[4] = CONREQUEST; // Message type
    memset(message + 5, 0, 3); // Padding
    memcpy(message + 8, dataContent, dataLength); // Data
    // Send the message
    if (mq_send(mq, message, totalSize, 0) == -1) {
        perror("mq_send");
        free(message);
        mq_close(mq);
        exit(EXIT_FAILURE);
    }
    printf("CONREQUEST message sent to server.\n");
    // Cleanup
    free(message);

    int cs_fd, sc_fd;
    // Open pipes
    cs_fd = open(cs_pipe, O_WRONLY);    
    sc_fd = open(sc_pipe, O_RDONLY);
    if (cs_fd == -1 || sc_fd == -1) {
        perror("Opening pipes failed");
        exit(1);
    }
    
    struct message isConReplyMsg;
    read(sc_fd, &isConReplyMsg, sizeof(isConReplyMsg) - sizeof(char*));

    // Verify message type
    if (isConReplyMsg.type == CONREPLY) {
        printf("CONREPLY message received.\n");
        char command[COMMAND_SIZE];

        if (file_path) {

            // Batch mode
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                perror("Failed to open command file");
                exit(EXIT_FAILURE);
            }

            while (fgets(command, sizeof(command), file) != NULL) {
                // Remove newline character at end of command
                size_t len = strlen(command);
                if (len > 0 && command[len - 1] == '\n') {
                    command[len - 1] = '\0';
                }

                // Prepare the message
                struct message mtemp;
                if (strcmp(command, "quit") == 0) {
                    
                    mtemp.type = QUITREQ;
                    mtemp.length = strlen("quit") + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for quit message data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, "quit", mtemp.length);

                    // Send the quit message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the quit message data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the quit message
                    break;
                }
                else if(strcmp(command, "quitall") == 0){
                    mtemp.type = QUITALL;
                    mtemp.length = strlen("quitall") + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for quit message data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, "quitall", mtemp.length);

                    // Send the quit message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the quit message data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the quit message
                    break;
                }
                else{
                    mtemp.type = COMLINE;
                    mtemp.length = strlen(command) + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for command data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, command, mtemp.length);

                    // Send the message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the command data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the command

                }

                // Receive COMREPLY message and print command output to terminal
                // Step 1: Read the message header first
                struct message receivedMsg;
                if (read(sc_fd, &receivedMsg, sizeof(receivedMsg) - sizeof(receivedMsg.data)) <= 0) {
                    perror("Failed to read message header");
                    exit(EXIT_FAILURE);
                }
                // Step 2: Allocate memory for incoming data
                receivedMsg.data = malloc(receivedMsg.length + 1); // +1 for null terminator
                if (!receivedMsg.data) {
                    perror("Failed to allocate memory for message data");
                    exit(EXIT_FAILURE);
                }
                // Step 3: Read the message data
                ssize_t totalBytesRead = 0;
                while (totalBytesRead < receivedMsg.length) {
                    ssize_t bytesRead = read(sc_fd, receivedMsg.data + totalBytesRead, receivedMsg.length - totalBytesRead);
                    if (bytesRead < 0) {
                        perror("Failed to read message data");
                        free(receivedMsg.data);
                        exit(EXIT_FAILURE);
                    } else if (bytesRead == 0) {
                        // Connection closed before all data was received
                        fprintf(stderr, "Connection closed prematurely\n");
                        free(receivedMsg.data);
                        exit(EXIT_FAILURE);
                    }
                    totalBytesRead += bytesRead;
                }
                receivedMsg.data[receivedMsg.length] = '\0'; // Null-terminate the data
                // Step 4: Print the received data
                if (receivedMsg.type == COMRESULT) {
                    printf("Command output:\n%s\n", receivedMsg.data);
                }
                // Cleanup
                free(receivedMsg.data);
                if (receivedMsg.type == QUITREPLY) {
                    break;
                }
            }
            fclose(file);
        } else {
            // Interactive mode
            while (1) {
                printf("Enter command: ");
                if (fgets(command, sizeof(command), stdin) == NULL) break;
                // Remove newline character at end of command
                size_t len = strlen(command);
                if (len > 0 && command[len - 1] == '\n') {
                    command[len - 1] = '\0';
                }
                
                struct message mtemp;
                if (strcmp(command, "quit") == 0) {
                    
                    mtemp.type = QUITREQ;
                    mtemp.length = strlen("quit") + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for quit message data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, "quit", mtemp.length);

                    // Send the quit message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the quit message data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the quit message
                    break;
                }
                else if(strcmp(command, "quitall") == 0){
                    mtemp.type = QUITALL;
                    mtemp.length = strlen("quitall") + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for quit message data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, "quitall", mtemp.length);

                    // Send the quit message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the quit message data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the quit message
                    break;
                }
                else{
                    mtemp.type = COMLINE;
                    mtemp.length = strlen(command) + 1;
                    mtemp.data = malloc(mtemp.length);
                    if (!mtemp.data) {
                        perror("Failed to allocate memory for command data");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(mtemp.data, command, mtemp.length);

                    // Send the message type and length first
                    write(cs_fd, &mtemp, sizeof(mtemp) - sizeof(char*));
                    // Then send the command data
                    write(cs_fd, mtemp.data, mtemp.length);

                    free(mtemp.data); // Free the allocated memory for the command
                }
                
                // Receive COMREPLY message and print command output to terminal
                // Step 1: Read the message header first
                struct message receivedMsg;
                if (read(sc_fd, &receivedMsg, sizeof(receivedMsg) - sizeof(receivedMsg.data)) <= 0) {
                    perror("Failed to read message header");
                    exit(EXIT_FAILURE);
                }
                // Step 2: Allocate memory for incoming data
                receivedMsg.data = malloc(receivedMsg.length + 1); // +1 for null terminator
                if (!receivedMsg.data) {
                    perror("Failed to allocate memory for message data");
                    exit(EXIT_FAILURE);
                }
                // Step 3: Read the message data
                ssize_t totalBytesRead = 0;
                while (totalBytesRead < receivedMsg.length) {
                    ssize_t bytesRead = read(sc_fd, receivedMsg.data + totalBytesRead, receivedMsg.length - totalBytesRead);
                    if (bytesRead < 0) {
                        perror("Failed to read message data");
                        free(receivedMsg.data);
                        exit(EXIT_FAILURE);
                    } else if (bytesRead == 0) {
                        // Connection closed before all data was received
                        fprintf(stderr, "Connection closed prematurely\n");
                        free(receivedMsg.data);
                        exit(EXIT_FAILURE);
                    }
                    totalBytesRead += bytesRead;
                }
                receivedMsg.data[receivedMsg.length] = '\0'; // Null-terminate the data
                // Step 4: Print the received data
                if (receivedMsg.type == COMRESULT) {
                    printf("Command output:\n%s\n", receivedMsg.data);
                }
                // Cleanup
                free(receivedMsg.data);
                // Check for exit condition (e.g., specific command)
                if (receivedMsg.type == QUITREPLY) {
                    break;
                }
            }
        }
    } else {
        printf("Received message is not a CONREPLY.\n");
    }
    // Close and remove pipes
    mq_close(mq);
    close(cs_fd);
    unlink(cs_pipe);
    close(sc_fd);
    unlink(sc_pipe);
    exit(0);
    return 0;
}