#include "tsl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 10

// Thread start function
void *thread_function(void *arg) {
    int *counter = (int *)arg;
    for (int i = 0; i < 1000; ++i) {
        // Simulate some work by incrementing a counter
        (*counter)++;
        // Yield control voluntarily
        tsl_yield(TSL_ANY);
    }
    // Call tsl_exit to indicate thread termination
    tsl_exit();
    return NULL;
}

int main() {
    int tid[NUM_THREADS];
    int counters[NUM_THREADS] = {0};
    struct timespec start, end;

    // Initialize the TSL library
    if (tsl_init(ALG_FCFS) != 0) {
        printf("Failed to initialize the TSL library\n");
        return -1;
    }

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        tid[i] = tsl_create_thread(thread_function, &counters[i]);
        if (tid[i] < 0) {
            printf("Failed to create thread\n");
            return -1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        tsl_join(tid[i]);
    }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate time taken
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("Total time taken by %d threads: %.9f seconds\n", NUM_THREADS, time_taken);

    return 0;
}
