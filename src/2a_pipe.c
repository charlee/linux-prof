#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "benchmark.h"

#define OP {pipe(fd);}
#define PRE
#define POST


int main() {

    uint64_t *times;
    char filename[256];
    int fd[2];

    uint64_t result;

    BENCHMARK(OP, PRE, POST, &result);
    printf("%ld\n", result);
}




