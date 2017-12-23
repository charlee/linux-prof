#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "benchmark.h"

#define OP {stat(filename, &statbuf);}
#define PRE {sprintf(filename, "f%d.tmp", rand());creat(filename, 0644);}
#define POST {unlink(filename);}


int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    struct stat statbuf;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}