#include <stdio.h>
#include <stdlib.h>
#include "tsl.h" // Make sure this is the correct header file for your library

#define NUM_THREADS 5
#define WORK_UNITS 10000

// Thread start function
void *thread_func(void *arg) {
    int yield_frequency = *(int *)arg;
    int work_done = 0;

    for (int i = 0; i < WORK_UNITS; ++i) {
        // Simulate some work
        work_done++;

        // Yield at the specified frequency
        if (i % yield_frequency == 0) {
            tsl_yield(TSL_ANY); // Change to actual yield function name if different
        }
    }

    printf("Thread completed with yield frequency %d.\n", yield_frequency);
    return NULL;
}

int main() {
    int tids[NUM_THREADS];
    int frequencies[NUM_THREADS] = {1, 10, 100, 1000, WORK_UNITS}; // Different yield frequencies

    // Initialize the threading library
    if (tsl_init(ALG_FCFS) != 0) { // Use the appropriate initialization function and check for success
        fprintf(stderr, "Failed to initialize the thread library.\n");
        return EXIT_FAILURE;
    }

    // Create threads with different yield frequencies
    for (int i = 0; i < NUM_THREADS; ++i) {
        tids[i] = tsl_create_thread(thread_func, &frequencies[i]); // Make sure to pass the frequency as argument
        if (tids[i] < 0) {
            fprintf(stderr, "Failed to create thread.\n");
            return EXIT_FAILURE;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        tsl_join(tids[i]); // Make sure to correctly wait for each thread to finish
    }

    printf("All threads completed.\n");
    return EXIT_SUCCESS;
}
