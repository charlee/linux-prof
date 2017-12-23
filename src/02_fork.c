#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "benchmark.h"

#define MAX_LOOP 1000

int main() {

    uint64_t *child_time;
    uint64_t result;
    uint64_t start, end1, end2;
    uint64_t parent_time;
    unsigned h0, l0, h1, l1, h2, l2;
    int fd[2];
    int val = 0;

    child_time = (uint64_t*)mmap(NULL, sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);

    WARMUP(h0, l0);

    pipe(fd);

    RDTSC(h0, l0);
    CALC_TIME(start, h0, l0);
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        RDTSCP(h2, l2);
        CALC_TIME(end2, h2, l2);

        close(fd[1]);
        read(fd[0], &val, sizeof(val));
        close(fd[0]);

        *child_time = end2-start;

        return 0;
    } else {
        // Parent process
        RDTSCP(h1, l1);
        CALC_TIME(end1, h1, l1);

        close(fd[0]);
        write(fd[1], &val, sizeof(val));
        close(fd[1]);

        wait(NULL);

        parent_time = end1 - start;
        if (parent_time > *child_time) {
            result = parent_time;
        } else {
            result = *child_time;
        }
        printf("%ld\n", result);
    }

}


