#include <stdio.h>
#include <time.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {stime(&time_data);}
#define PRE {time(&time_data);}
#define POST


int main() {

    uint64_t *times;
    time_t time_data;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}



