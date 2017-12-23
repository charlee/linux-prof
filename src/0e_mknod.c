#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "benchmark.h"

#define OP {mknod(filename, S_IRUSR|S_IWUSR|S_IFREG, 0);}
#define PRE {sprintf(filename, "f%d.tmp", rand());}
#define POST {unlink(filename);}


int main() {

    uint64_t result;
    char filename[256];

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}


