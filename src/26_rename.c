#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {rename(filename, new_filename);}
#define PRE {sprintf(filename, "f%d.tmp", rand());sprintf(new_filename, "nf%d.tmp", rand());creat(filename, 0644);}
#define POST {unlink(new_filename);}


int main() {

    uint64_t *times;
    char filename[256];
    char new_filename[256];
    struct stat statbuf;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}
