#include <stdio.h>
#include <stdint.h>

#if UINTPTR_MAX == 0xffffffff
    /* 32-bit */
    typedef uint32_t address_size_t;
#elif UINTPTR_MAX == 0xffffffffffffffff
    /* 64-bit */
    typedef uint64_t address_size_t;
#else
    /* wtf */
#endif


#define OFFSET_OF(struct_name, struct_field)   \
    (address_size_t)&((struct_name *)0)->struct_field

typedef struct _test_struct_t {
    char name[10];
    int a;
    float pi;
    int c;
} test_struct_t;


int main() {
    test_struct_t w;
    printf("strcture address: %p\n", &w);
    printf("offset name: 0x%x\n", (uint32_t)OFFSET_OF(test_struct_t, name));
    printf("offset a: 0x%x, %p\n", (uint32_t)OFFSET_OF(test_struct_t, a), (&w.a)-OFFSET_OF(test_struct_t, a));
    printf("offset pi: 0x%x, %p\n", (uint32_t)OFFSET_OF(test_struct_t, pi), (&w.pi)-OFFSET_OF(test_struct_t, pi));
    printf("offset c: 0x%x, %p\n", (uint32_t)OFFSET_OF(test_struct_t, c), (&w.c)-OFFSET_OF(test_struct_t, c));

}



