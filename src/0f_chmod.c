#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "benchmark.h"

#define OP {chmod(filename, 0777);}
#define PRE {sprintf(filename, "f%d.tmp", rand());creat(filename, 0644);}
#define POST {unlink(filename);}


int main() {

    uint64_t result;
    int fd;

    char filename[256];

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}



