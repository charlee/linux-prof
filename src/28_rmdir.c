#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "benchmark.h"

#define OP {rmdir(dirname);}
#define PRE {sprintf(dirname, "f%d.tmp", rand());mkdir(dirname, 0755);}
#define POST


int main() {

    uint64_t *times;
    char dirname[256];
    uint64_t result;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}


