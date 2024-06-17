#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsl.h"

#define TSL_ERROR -1

void *minimal_thread_function(void *arg) { return NULL; } // Minimal thread work

int main() {
    const int NUM_THREADS = 255; 
    struct timespec start, end;

    if (tsl_init(ALG_FCFS) == TSL_ERROR) { 
        fprintf(stderr, "Failed to initialize threading library.\n");
        return EXIT_FAILURE;
    }

    clock_gettime(CLOCK_MONOTONIC, &start); // Start timing

    for (int i = 0; i < NUM_THREADS; ++i) {
        int tid = tsl_create_thread(minimal_thread_function, NULL);
        if (tid == TSL_ERROR) {
            fprintf(stderr, "Failed to create thread\n");
            return EXIT_FAILURE;
        }

        tsl_join(tid); 
    }

    clock_gettime(CLOCK_MONOTONIC, &end); // Stop timing

    // Calculate and display the elapsed time
    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time taken for %d thread creations and destructions: %f seconds\n", NUM_THREADS, elapsed_time);

    return EXIT_SUCCESS;
}