#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define TMP_FILE_NAME "tmp_link_test"
#define MAX_LOOP 1000

#define OP {unlink(filename);}
#define PRE {sprintf(filename, "f%d.tmp", rand()); close(creat(filename, 0644));}
#define POST

int main() {

    uint64_t *times;
    char filename[256];
    int fd;

    BENCHMARK(OP, PRE, POST, times, MAX_LOOP);

    for (int i = 0; i < MAX_LOOP; i++) {
        printf("%ld\n", (times[i]));
    }

    free(times);
}


