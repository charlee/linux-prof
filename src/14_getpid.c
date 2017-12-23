#include <stdio.h>
#include <unistd.h>

#include "benchmark.h"

#define MAX_LOOP 1000

#define OP {asm volatile("mov $20, %eax\n\t" "int $0x80\n\t");}
#define PRE
#define POST

int main() {

    uint64_t *times;
    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}