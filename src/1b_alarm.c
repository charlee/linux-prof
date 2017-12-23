#include <stdio.h>
#include <unistd.h>

#include "benchmark.h"

#define OP {alarm(10);}
#define PRE
#define POST {alarm(0);}

int main() {

    uint64_t result;
    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
