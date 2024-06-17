#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include "mf.h"

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    printf("\nReceived signal %d, cleaning up...\n", sig);
    if (mf_destroy() == MF_SUCCESS) {
        printf("Cleanup successful.\n");
    } else {
        fprintf(stderr, "Error during cleanup.\n");
    }
    exit(EXIT_SUCCESS); // Exit after cleanup
}

int main() {
    // Register signal handler for SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot set signal handler.\n");
        return EXIT_FAILURE;
    }

    printf("mfserver started, PID: %d\n", getpid());

    // Initialize the message facility
    if (mf_init() == MF_SUCCESS) {
        printf("Message facility initialized successfully.\n");
    } else {
        fprintf(stderr, "Failed to initialize message facility.\n");
        return EXIT_FAILURE;
    }

    // Server main loop - sleeps indefinitely in this example
    // The server does minimal work and waits for a signal to initiate cleanup.
    while (1) {
        pause(); // Wait for signals
    }

    // This point is never reached because the server exits from the signal handler
    return EXIT_SUCCESS;
}