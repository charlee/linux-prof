#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "benchmark.h"

#define MAX_LOOP 1000
#define WRITE_SIZE 4096

#define OP {mknod(filename, S_IRUSR|S_IWUSR|S_IFREG, 0);}
#define PRE {sprintf(filename, "f%d.tmp", rand());}
#define POST {unlink(filename);}


int main() {

    uint64_t *times;
    int fd;

    char *data;
    char filename[256];

    data = (char*)malloc(WRITE_SIZE);
    memset(data, 1, WRITE_SIZE);

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    free(data);
    CLEANUP(times, MAX_LOOP);
}


