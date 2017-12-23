#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define OP {fp = open(filename, O_CREAT);}
#define PRE {sprintf(filename, "f%d.tmp", rand());}
#define POST {close(fp); unlink(filename);}

int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    int fp;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
