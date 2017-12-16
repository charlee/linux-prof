#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {write(fd, data, WRITE_SIZE);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC, 0644);}
#define POST {close(fd); unlink(filename);}


int main() {

    uint64_t *times;
    int fd;

    char *data;
    char filename[256];

    data = (char*)malloc(WRITE_SIZE);
    memset(data, 1, WRITE_SIZE);

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    free(data);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }
}

