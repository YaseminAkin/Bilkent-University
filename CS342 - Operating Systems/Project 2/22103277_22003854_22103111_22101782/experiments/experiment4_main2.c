#include "tsl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COUNT 1000000

// Shared counter and lock for synchronization
volatile int counter = 0;

// Thread function for incrementing the counter
void *increment_function(void *arg) {
    while (counter < MAX_COUNT) {
        counter++;
        // Voluntarily yield control after each increment
        tsl_yield(TSL_ANY);
    }
    tsl_exit();
    return NULL;
}

int main() {
    struct timespec start, end;

    // Initialize the TSL library
    if (tsl_init(ALG_FCFS) != 0) {
        printf("Failed to initialize TSL library\n");
        return -1;
    }

    // Create two threads
    int tid1 = tsl_create_thread(increment_function, NULL);
    int tid2 = tsl_create_thread(increment_function, NULL);

    if (tid1 < 0 || tid2 < 0) {
        printf("Failed to create threads\n");
        return -1;
    }

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Wait for both threads to complete
    tsl_join(tid1);
    tsl_join(tid2);

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate and print the elapsed time
    double elapsed_time = end.tv_sec - start.tv_sec;
    elapsed_time += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("With Context Switching: %.9f seconds\n", elapsed_time);

    return 0;
}
