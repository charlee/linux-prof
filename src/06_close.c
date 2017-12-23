#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define OP {close(fp);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); fp = open(filename, O_CREAT);}
#define POST {unlink(filename);}

int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    int fp;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
