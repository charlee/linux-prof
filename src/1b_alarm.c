#include <stdio.h>
#include <unistd.h>

#include "benchmark.h"

#define MAX_LOOP 1000

#define OP {alarm(10);}
#define PRE
#define POST {alarm(0);}

int main() {

    uint64_t *times;
    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    CLEANUP(times, MAX_LOOP);
}
