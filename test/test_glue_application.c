#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include "gl_dblinklist.h"

#if UINTPTR_MAX == 0xffffffff
    /* 32-bit */
    typedef uint32_t address_size_t;
#elif UINTPTR_MAX == 0xffffffffffffffff
    /* 64-bit */
    typedef uint64_t address_size_t;
#else
    /* wtf */
#endif


typedef struct _test_struct_t {
    char name[20];
    int a;
    int b;
    gl_node_t node;
} test_struct_t;


int main(void) {
    printf("start \n");

    test_struct_t n0 = {.name = "I am root." , .a = 0, .node.left = NULL, .node.right = NULL};
    test_struct_t n1 = {.name = "I am node1.", .a = 1, .node.left = NULL, .node.right = NULL};
    test_struct_t n2 = {.name = "I am node2.", .a = 2, .node.left = NULL, .node.right = NULL};
    test_struct_t n3 = {.name = "I am node3.", .a = 3, .node.left = NULL, .node.right = NULL};
    test_struct_t n4 = {.name = "I am node4.", .a = 4, .node.left = NULL, .node.right = NULL};

    insert_gllinklist(&n0.node, &n1.node);
    insert_gllinklist(&n1.node, &n2.node);
    insert_gllinklist(&n2.node, &n3.node);
    insert_gllinklist(&n3.node, &n4.node);

    printf("=>%p\n", &n0);

    gl_node_t *temp_node;
    test_struct_t *struct_prt;
    ITERATE_GL_TREE_BEGIN(&n0.node, temp_node) {
        struct_prt = (test_struct_t *)((address_size_t)temp_node - (address_size_t)OFFSET_OF(test_struct_t, node));
        printf("%s\n", struct_prt->name);
    } ITERATE_GL_TREE_END;

    printf("end\n");
    return 0;
}

