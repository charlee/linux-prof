#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "benchmark.h"

#define OP {mkdir(dirname, 0755);}
#define PRE {sprintf(dirname, "f%d.tmp", rand());}
#define POST {rmdir(dirname);}


int main() {

    uint64_t *times;
    uint64_t result;
    char dirname[256];

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}

