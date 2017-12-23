#include <stdio.h>
#include <unistd.h>

#include "benchmark.h"

#define OP {asm volatile("mov $20, %eax\n\t" "int $0x80\n\t");}
#define PRE
#define POST

int main() {

    uint64_t *times;
    uint64_t result;
    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}