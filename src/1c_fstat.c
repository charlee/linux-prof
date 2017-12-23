#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "benchmark.h"

#define OP {fstat(fd, &statbuf);}
#define PRE {sprintf(filename, "f%d.tmp", rand());fd = creat(filename, 0644);}
#define POST {close(fd); unlink(filename);}


int main() {

    uint64_t result;
    int fd;

    char filename[256];
    struct stat statbuf;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}
