/**
 * TODO: Exec cycles decreases on each execute..
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "benchmark.h"

#define TMP_FILE_NAME "tmp_link_test"

#define SCRIPT "#!/bin/sh\n"

#define OP {execve(filename, new_argv, new_env);}
#define PRE {sprintf(filename, "f%d.tmp.sh", rand()); fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC, 0644); write(fd, data, 10); close(fd);}
#define POST {unlink(filename);}

int main() {

    uint64_t result;
    char filename[256];
    int fd;

    char *new_argv[] = {NULL, NULL};
    char *new_env[] = {NULL};

    char data[11] = SCRIPT;

    BENCHMARK(OP, PRE, POST, &result);

    printf("%ld\n", result);
}



