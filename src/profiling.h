#include <time.h>
#include <stdio.h>

#define TIMESTAMP(o) clock_gettime(CLOCK_MONOTONIC, &o)

#define TIME_THIS(op) \
    ({ \
        struct timespec __start_time, __end_time;\
        long __consumed = 0;\
        TIMESTAMP(__start_time);\
        op; \
        TIMESTAMP(__end_time);\
        __consumed = __end_time.tv_nsec - __start_time.tv_nsec;\
        if (__consumed < 0) {\
            __consumed += 1000000000;\
        }\
        printf("%ld\n", __consumed);\
    })

