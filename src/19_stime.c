#include <stdio.h>
#include <time.h>

#include "benchmark.h"

#define OP {stime(&time_data);}
#define PRE {time(&time_data);}
#define POST


int main() {

    uint64_t *times;
    uint64_t result;
    time_t time_data;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}



