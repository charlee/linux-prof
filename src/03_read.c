#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define READ_SIZE 4096

#define OP {read(fp, data, READ_SIZE);}
#define PRE
#define POST


int main() {

    uint64_t *times;
    int fp;

    char *data;

    data = (char*)malloc(READ_SIZE);

    fp = open("/dev/zero", O_RDONLY);

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    close(fp);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    free(data);
    free(times);
}

