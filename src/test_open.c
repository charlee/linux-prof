#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000

#define OP {fp = open(filename, O_CREAT);}
#define PRE {sprintf(filename, "f%d.tmp", rand());}
#define POST {close(fp); unlink(filename);}

int main() {

    uint64_t *times;
    char filename[256];
    int fp;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }
}
