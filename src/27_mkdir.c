#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {mkdir(dirname, 0755);}
#define PRE {sprintf(dirname, "f%d.tmp", rand());}
#define POST {rmdir(dirname);}


int main() {

    uint64_t *times;
    char dirname[256];

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}

