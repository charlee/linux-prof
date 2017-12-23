#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define TMP_FILE_NAME "tmp_link_test"

#define OP {link(TMP_FILE_NAME, filename);}
#define PRE {sprintf(filename, "f%d.tmp", rand());}
#define POST {unlink(filename);}

int main() {

    uint64_t *times;
    uint64_t result;
    char filename[256];
    int fd;

    fd = creat(TMP_FILE_NAME, 0644);
    close(fd);

    BENCHMARK(OP, PRE, POST, &result);

    unlink(TMP_FILE_NAME);
    printf("%ld\n", result);
}

