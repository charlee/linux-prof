#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>

#include "benchmark.h"

#define OP {utime(filename, NULL);}
#define PRE {sprintf(filename, "f%d.tmp", rand());creat(filename, 0644);}
#define POST {unlink(filename);}


int main() {

    uint64_t result;
    char filename[256];

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
