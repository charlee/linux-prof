#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define RDTSC(xh, xl) \
asm volatile("CPUID\n\t" \
             "RDTSC\n\t" \
             "mov %%edx, %0\n\t" \
             "mov %%eax, %1\n\t" : "=r" (xh), "=r" (xl)::"%rax", "%rbx", "%rcx", "%rdx")


#define RDTSCP(xh, xl) \
asm volatile("RDTSCP\n\t" \
             "mov %%edx, %0\n\t" \
             "mov %%eax, %1\n\t" \
             "CPUID\n\t" : "=r" (xh), "=r" (xl)::"%rax", "%rbx", "%rcx", "%rdx")
            

#define CALC_TIME(x, xh, xl) x = (((uint64_t)(xh) << 32) | (xl))

#define WARMUP1(xh, xl) RDTSC(xh, xl); RDTSCP(xh, xl)
#define WARMUP(xh, xl) WARMUP1(xh, xl); WARMUP1(xh, xl); WARMUP1(xh, xl);

#define BENCHMARK(op, pre, post, result_ptr, count) \
    uint64_t __start, __end; \
    uint64_t __i; \
    unsigned __h0, __l0, __h1, __l1; \
    pid_t __pid; \
    result_ptr = (uint64_t*)mmap(NULL, sizeof(uint64_t)*count, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0);\
    pre; \
    op; \
    post; \
    WARMUP(__h0, __l0); \
    for (__i=0; __i<count; __i++) { \
        __pid = fork(); \
        if (__pid == 0) { \
            pre; \
            RDTSC(__h0, __l0); \
            op; \
            RDTSCP(__h1, __l1); \
            CALC_TIME(__start, __h0, __l0); \
            CALC_TIME(__end, __h1, __l1); \
            result_ptr[__i] = __end - __start;\
            post; \
            return 0; \
        } else { \
            wait(NULL); \
        } \
    }


#define CLEANUP(result_ptr, count) munmap(result_ptr, sizeof(uint64_t) * count)