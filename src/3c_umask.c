#include <stdio.h>
#include <sys/stat.h>

#include "benchmark.h"

#define WRITE_SIZE 4096

#define OP {umask(0200);}
#define PRE
#define POST


int main() {

    uint64_t result;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}



