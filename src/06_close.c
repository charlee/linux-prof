#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000

#define OP {close(fp);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); fp = open(filename, O_CREAT);}
#define POST {unlink(filename);}

int main() {

    uint64_t *times;
    char filename[256];
    int fp;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}
