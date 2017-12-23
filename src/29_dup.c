#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {dup(fd);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); fd = creat(filename, 0644);}
#define POST {close(fd); unlink(filename);}


int main() {

    uint64_t *times;
    char filename[256];
    int fd;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}



