#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define READ_SIZE 4096

#define OP {read(fp, data, READ_SIZE);}
#define PRE
#define POST


int main() {

    uint64_t *times;
    uint64_t result;
    int fp;

    char *data;

    data = (char*)malloc(READ_SIZE);

    fp = open("/dev/zero", O_RDONLY);

    BENCHMARK(OP, PRE, POST, &result);

    close(fp);

    printf("%ld\n", result);

    free(data);
}

