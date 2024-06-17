#include <stdio.h>
#include <time.h>

#define MAX_COUNT 1000000

int main() {
    struct timespec start, end;
    int counter = 0;

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Increment counter without yielding
    for (int i = 0; i < MAX_COUNT; ++i) {
        counter++;
    }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate and print the elapsed time
    double elapsed_time = end.tv_sec - start.tv_sec;
    elapsed_time += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Baseline (No Context Switching): %.9f seconds\n", elapsed_time);

    return 0;
}
