#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "benchmark.h"

#define OP {rename(filename, new_filename);}
#define PRE {sprintf(filename, "f%d.tmp", rand());sprintf(new_filename, "nf%d.tmp", rand());creat(filename, 0644);}
#define POST {unlink(new_filename);}


int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    char new_filename[256];
    struct stat statbuf;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
