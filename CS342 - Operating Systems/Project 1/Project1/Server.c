#include <stdlib.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/time.h>

#include "message.h"

// Global variables to keep track of server child and client processes
pid_t child_pids[MAX_CLIENTS];
int num_children = 0;
pid_t client_pids[MAX_CLIENTS];
int num_clients = 0;
volatile sig_atomic_t keep_running = 1;

// Signal handler function to handle the termination signal
void handle_termination_signal(int signum) {
    exit(0);
}

void check_and_remove_terminated_children(void) {
    int status;
    pid_t terminated_pid;

    for (int i = 0; i < num_children; ) {
        terminated_pid = waitpid(child_pids[i], &status, WNOHANG);

        if (terminated_pid > 0) {
            // Child terminated. Remove it from the array
            for (int j = i; j < num_children - 1; ++j) {
                child_pids[j] = child_pids[j + 1];
            }
            num_children--; // Decrement the count of active children
        } else {
            // No change, move to the next child
            i++;
        }
    }
}

int main(int argc, char const *argv[]) {

    // First handle the argument 
    if (argc != 2) { // Ensure exactly MQNAME is provided
        fprintf(stderr, "Usage: %s MQNAME\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* mqName = argv[1]; // The first (and only) argument is MQNAME

    mqd_t mq;
    struct mq_attr attr;
    // Set up the message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = BUFFER_SIZE;
    attr.mq_curmsgs = 0;
    // Open the message queue for both reading and writing
    mq = mq_open(mqName, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    signal(SIGTERM, handle_termination_signal);

    // Server main loop
    while (keep_running) {

        check_and_remove_terminated_children();

        //Receice CONREQUEST messages
        char buffer[BUFFER_SIZE + 1];
        // Receive message from the queue
        ssize_t bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        // Ensure the message is properly terminated
        buffer[bytes_read] = '\0';
        // Extract the message type
        uint8_t messageType = buffer[4];        

        if (messageType == CONREQUEST) {

            printf("number of child: %d \n", num_children);
            if(num_children == MAX_CLIENTS) {
                printf("MAXCLIENTS is reached, cannot connect further clients! Quit one and try again later!");
                continue;
            }
            
            // Parse the buffer to extract client ID, pipe names, and wsize from the COMREQUEST message
            int client_id, wsize;
            char cs_pipe[100], sc_pipe[100]; // Adjust size as needed
            if (sscanf(buffer + 8, "%d %s %s %d", &client_id, cs_pipe, sc_pipe, &wsize) == 4) {
                printf("server main: CONREQUEST message received: pid=%d, cs=%s, sc=%s, wsize=%d\n", client_id, cs_pipe, sc_pipe, wsize);
                int extracted_client_id;
                sscanf(cs_pipe, "/tmp/cs_pipe_%d", &extracted_client_id);
                client_pids[num_clients++] = extracted_client_id;
                // Fork a child server process to handle this client
                pid_t pid = fork();
                if (pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (pid == 0) {
                    int cs_fd, sc_fd;
                    int childsReal = getppid();
                    
                    // Wait and try to open the client-to-server pipe for reading
                    while((cs_fd = open(cs_pipe, O_RDONLY)) == -1) {
                        if(errno != ENOENT) { // If error is not "No such file or directory"
                            perror("Failed to open CS_PIPE");
                            exit(EXIT_FAILURE);
                        }
                        // Optional: Sleep for a short period before retrying
                        sleep(1);
                    }

                    // Similarly, wait and try to open the server-to-client pipe for writing
                    while((sc_fd = open(sc_pipe, O_WRONLY)) == -1) {
                        if(errno != ENOENT) {
                            perror("Failed to open SC_PIPE");
                            exit(EXIT_FAILURE);
                        }
                        sleep(1);
                    }

                    // Send CONREPLY message
                    struct message conReplyMsg;
                    conReplyMsg.type = CONREPLY;
                    write(sc_fd, &conReplyMsg, sizeof(conReplyMsg) - sizeof(char*));

                    // Server logic to read from cs_fd and write responses to sc_fd
                    while (1) {
                        // Receive messages from cs_pipe
                        struct message receivedMsg;
                        ssize_t num_read = read(cs_fd, &receivedMsg, sizeof(receivedMsg) - sizeof(char*)); // Read the message excluding the data pointer
                        if (num_read <= 0) break; // Check for read error or end of input
                        // Allocate memory for data based on the length received in receivedMsg
                        receivedMsg.data = malloc(receivedMsg.length + 1); // +1 for null terminator, if needed
                        // Check if allocation was successful
                        if (receivedMsg.data == NULL) {
                            // Handle allocation failure
                            perror("Failed to allocate memory for data");
                            exit(EXIT_FAILURE);
                        }
                        // Now, read the actual data based on the length specified in receivedMsg
                        num_read = read(cs_fd, receivedMsg.data, receivedMsg.length);
                        if (num_read <= 0) {
                            // Handle read error or unexpected end of data
                            free(receivedMsg.data); // Don't forget to free allocated memory in case of error
                            break;
                        }
                        // Ensure the received data is null-terminated, if you're treating it as a string
                        receivedMsg.data[receivedMsg.length] = '\0';

                        if (receivedMsg.type == COMLINE) {

                            printf("server child: COMLINE message received: len=%d, type=%d, data=%s\n", receivedMsg.length + 8, receivedMsg.type, receivedMsg.data);
                            char* command = receivedMsg.data;
                            char* verticalLine = strchr(command, '|');

                            char tempFileName[64]; // Buffer to hold the unique file name
                            sprintf(tempFileName, "temp_output_%d.txt", getpid()); // Create unique file names

                            if (verticalLine != NULL) {
                                // Split the command into two parts at the '|'
                                *verticalLine = '\0';
                                char* cmd1 = command;
                                char* cmd2 = verticalLine + 1;

                                int fd[2];
                                if (pipe(fd) == -1) {
                                    perror("Pipe failed");
                                    exit(EXIT_FAILURE);
                                }

                                if (fork() == 0) {
                                    // Child 1 - executes cmd1 and writes to pipe
                                    close(fd[0]);
                                    dup2(fd[1], STDOUT_FILENO);
                                    close(fd[1]);

                                    char* command = "/bin/sh";
                                    char* args[] = {"sh", "-c", cmd1, NULL};
                                    execvp(command, args);
                                    perror("execvp failed");
                                    exit(EXIT_FAILURE);
                                }

                                if (fork() == 0) {
                                    // Child 2 - executes cmd2 and reads from pipe
                                    close(fd[1]);
                                    dup2(fd[0], STDIN_FILENO);
                                    close(fd[0]);

                                    // Open temporary file
                                    int temp_fd = open(tempFileName, O_RDWR | O_CREAT | O_TRUNC, 0600);
                                    if (temp_fd < 0) {
                                        perror("Open temporary file failed");
                                        exit(EXIT_FAILURE);
                                    }

                                    // Redirect stdout to temporary file
                                    dup2(temp_fd, STDOUT_FILENO);
                                    close(temp_fd);

                                    char* command = "/bin/sh";
                                    char* args[] = {"sh", "-c", cmd2, NULL};
                                    execvp(command, args);
                                    perror("execvp failed");
                                    exit(EXIT_FAILURE);
                                }

                                // Parent - close both ends of the pipe and wait for children
                                close(fd[0]);
                                close(fd[1]);
                                wait(NULL);
                                wait(NULL);

                                // Send COMRESULT message
                                struct message resultMsg;
                                resultMsg.type = COMRESULT; // Set message type to COMRESULT

                                // Allocate memory for the data field dynamically based on file size
                                FILE* temp_file = fopen(tempFileName, "r");
                                if (!temp_file) {
                                    perror("Open temporary file for reading failed");
                                    exit(EXIT_FAILURE);
                                }

                                // Seek to the end of the file to determine its size
                                fseek(temp_file, 0, SEEK_END);
                                long fileSize = ftell(temp_file);
                                rewind(temp_file); // Go back to the start of the file

                                resultMsg.data = (char*)malloc(fileSize + 1); // +1 for null terminator
                                if (!resultMsg.data) {
                                    perror("Memory allocation failed");
                                    fclose(temp_file);
                                    exit(EXIT_FAILURE);
                                }

                                // Read file content into resultMsg.data
                                size_t bytesRead = fread(resultMsg.data, 1, fileSize, temp_file);
                                resultMsg.data[bytesRead] = '\0'; // Null-terminate the string
                                resultMsg.length = bytesRead;

                                // Send the COMRESULT message header
                                write(sc_fd, &resultMsg, sizeof(resultMsg) - sizeof(resultMsg.data)); // Exclude the pointer from the write

                                // Send the COMRESULT message data separately
                                ssize_t bytesSent = 0;
                                while (bytesSent < resultMsg.length) {
                                    ssize_t chunkSize = (resultMsg.length - bytesSent > wsize) ? wsize : (resultMsg.length - bytesSent);
                                    ssize_t writeResult = write(sc_fd, resultMsg.data + bytesSent, chunkSize);
                                    if (writeResult == -1) {
                                        perror("Failed to write to SC_PIPE");
                                        exit(EXIT_FAILURE);
                                    }
                                    bytesSent += writeResult;
                                }

                                free(resultMsg.data); // Free the allocated memory
                                fclose(temp_file);
                                unlink(tempFileName); // Delete the temporary file
                            } else {

                                pid_t pid = fork();
                                if (pid == 0) { // Child process
                                    // Open temporary file
                                    int temp_fd = open(tempFileName, O_RDWR | O_CREAT | O_TRUNC, 0600);
                                    if (temp_fd < 0) {
                                        perror("Open temporary file failed");
                                        exit(EXIT_FAILURE);
                                    }

                                    // Redirect stdout to temporary file
                                    dup2(temp_fd, STDOUT_FILENO);
                                    close(temp_fd);

                                    // Execute the command using execlp or execvp
                                    char* command = "/bin/sh";
                                    char* args[] = {"sh", "-c", receivedMsg.data, NULL};
                                    execvp(command, args);
                                    perror("execvp failed"); // execvp returns only on error
                                    exit(EXIT_FAILURE);

                                } else if (pid > 0) { // Parent process
                                    int status;
                                    waitpid(pid, &status, 0); // Wait for child to finish

                                    // Send COMRESULT message
                                    struct message resultMsg;
                                    resultMsg.type = COMRESULT; // Set message type to COMRESULT

                                    // Allocate memory for the data field dynamically based on file size
                                    FILE* temp_file = fopen(tempFileName, "r");
                                    if (!temp_file) {
                                        perror("Open temporary file for reading failed");
                                        exit(EXIT_FAILURE);
                                    }

                                    // Seek to the end of the file to determine its size
                                    fseek(temp_file, 0, SEEK_END);
                                    long fileSize = ftell(temp_file);
                                    rewind(temp_file); // Go back to the start of the file

                                    resultMsg.data = (char*)malloc(fileSize + 1); // +1 for null terminator
                                    if (!resultMsg.data) {
                                        perror("Memory allocation failed");
                                        fclose(temp_file);
                                        exit(EXIT_FAILURE);
                                    }

                                    // Read file content into resultMsg.data
                                    size_t bytesRead = fread(resultMsg.data, 1, fileSize, temp_file);
                                    resultMsg.data[bytesRead] = '\0'; // Null-terminate the string
                                    resultMsg.length = bytesRead;

                                    // Send the COMRESULT message header
                                    write(sc_fd, &resultMsg, sizeof(resultMsg) - sizeof(resultMsg.data)); // Exclude the pointer from the write

                                    // Send the COMRESULT message data separately
                                    // Assuming resultMsg.data and resultMsg.length are set up correctly
                                    ssize_t bytesSent = 0;
                                    while (bytesSent < resultMsg.length) {
                                        ssize_t chunkSize = (resultMsg.length - bytesSent > wsize) ? wsize : (resultMsg.length - bytesSent);
                                        ssize_t writeResult = write(sc_fd, resultMsg.data + bytesSent, chunkSize);
                                        if (writeResult == -1) {
                                            perror("Failed to write to SC_PIPE");
                                            exit(EXIT_FAILURE);
                                        }
                                        bytesSent += writeResult;
                                    }

                                    free(resultMsg.data); // Free the allocated memory
                                    fclose(temp_file);
                                    unlink(tempFileName); // Delete the temporary file
                                } else {
                                    perror("Fork failed");
                                    exit(EXIT_FAILURE);
                                }   
                            }
                            printf("command execution finished\n");
                        }
                        else if(receivedMsg.type == QUITREQ) {
                            printf("server child: QUITREQ message is received: len=%d, type=%d\n", receivedMsg.length + 8, receivedMsg.type);
                            // Handle QUITREQ message
                            struct message replyMsg;
                            replyMsg.type = QUITREPLY;
                            replyMsg.length = 0;
                            write(sc_fd, &replyMsg, sizeof(replyMsg) - sizeof(replyMsg.data));
                            printf("number of child: %d", num_children);
                            exit(0);
                        }
                        else if (receivedMsg.type == QUITALL) {
                            printf("server child: QUITALL message is received: len=%d, type=%d\n", receivedMsg.length + 8, receivedMsg.type);
                            // Handle QUITALL message
                            keep_running = 0;
                            struct message replyMsg;
                            replyMsg.type = QUITREPLY;
                            replyMsg.length = 0;
                            write(sc_fd, &replyMsg, sizeof(replyMsg) - sizeof(replyMsg.data)); // Send the QUITREPLY message header

                            for (int i = 0; i < num_children; i++) {
                                kill(child_pids[i], SIGTERM); // Terminate child processes
                            }
                            for (int i = 0; i < num_children; i++) {
                                kill(child_pids[i], SIGTERM); // Terminate child processes
                            }
                            printf("command execution finished\n");
                            break; // Break out of the loop to terminate the child process
                        }
                        else {
                            // Handle unknown message type
                            fprintf(stderr, "Unknown message type: %d\n", receivedMsg.type);
                        }
                    }
                    // Close pipes
                    close(cs_fd);
                    close(sc_fd);
                    exit(0); // Terminate child process after handling the client
                }
                else{
                    // Parent process continues back to the start of the loop to listen for more messages
                    child_pids[num_children++] = pid; // Store child PID
                }
            } else {
                fprintf(stderr, "Error parsing CONREQUEST data.\n");
            }
        }else{
            fprintf(stderr, "Received message of unexpected type: %d\n", messageType);
        }
    }
    // Cleanup
    mq_close(mq);
    mq_unlink(mqName);
    return 0;
}