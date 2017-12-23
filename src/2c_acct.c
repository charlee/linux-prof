#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "benchmark.h"

#define WRITE_SIZE 4096

#define OP {acct(filename);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); open(filename, O_CREAT|O_WRONLY|O_TRUNC, 0644); close(fd);}
#define POST {acct(NULL); unlink(filename);}


int main() {

    uint64_t result;
    int fd;
    char filename[256];

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}


