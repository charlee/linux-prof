#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "benchmark.h"

#define OP {dup(fd);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); fd = creat(filename, 0644);}
#define POST {close(fd); unlink(filename);}


int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    int fd;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}



