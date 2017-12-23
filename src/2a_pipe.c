#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "benchmark.h"

#define MAX_LOOP 1000

#define OP {pipe(fd);}
#define PRE
#define POST


int main() {

    uint64_t *times;
    char filename[256];
    int fd[2];

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}




