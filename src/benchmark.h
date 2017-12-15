#include <stdint.h>
#include <stdlib.h>

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

#define BENCHMARK(op, result_ptr, count) \
    uint64_t __start, __end; \
    uint64_t __i; \
    unsigned __h0, __l0, __h1, __l1; \
    result_ptr = (uint64_t*)malloc(count * sizeof(uint64_t));\
    WARMUP(__h0, __l0); \
    for (__i=0; __i<count; __i++) { \
        RDTSC(__h0, __l0); \
        op; \
        RDTSCP(__h1, __l1); \
        CALC_TIME(__start, __h0, __l0); \
        CALC_TIME(__end, __h1, __l1); \
        result_ptr[__i] = __end - __start;\
    }
