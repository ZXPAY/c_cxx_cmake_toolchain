#include <stdio.h>
#include <stdint.h>

#define OFFSET_OF(struct_name, struct_field)   \
    (uint64_t)&((struct_name *)0)->struct_field

typedef struct _test_struct_t {
    char name[10];
    int a;
    float pi;
    int c;
} test_struct_t;


int main() {
    test_struct_t w;
    printf("strcture address: %p\n", &w);
    printf("offset name: %ld\n", OFFSET_OF(test_struct_t, name));
    printf("offset a: %ld, %lx\n", OFFSET_OF(test_struct_t, a), (uint64_t)(&w.a)-OFFSET_OF(test_struct_t, a));
    printf("offset pi: %ld, %lx\n", OFFSET_OF(test_struct_t, pi), (uint64_t)(&w.pi)-OFFSET_OF(test_struct_t, pi));
    printf("offset c: %ld, %lx\n", OFFSET_OF(test_struct_t, c), (uint64_t)(&w.c)-OFFSET_OF(test_struct_t, c));

}



