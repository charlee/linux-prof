#include <stdio.h>
#include <sys/times.h>

#include "benchmark.h"

#define OP {times(&buf);}
#define PRE
#define POST

int main() {

    uint64_t result;
    struct tms buf;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
