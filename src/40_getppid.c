#include <stdio.h>
#include <unistd.h>

#include "benchmark.h"

#define OP {getppid();}
#define PRE
#define POST

int main() {

    uint64_t result;
    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}