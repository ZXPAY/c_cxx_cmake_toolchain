#include <stdio.h>
#include <string.h>
#include "tree.h"

int main(void) {
    printf("start testing\n");

    tree_node_t root;
    tree_node_t n1, n2, n3, n4, n5, n6;
    
    int n0_para = 0;
    int n1_para = 1;
    int n2_para = 2;
    int n3_para = 3;
    int n4_para = 4;
    int n5_para = 5;
    int n6_para = 6;

    // Manual initialize
    root.left = &n1;
    root.right = &n5;
    root.para = (int *)&n0_para;

    n1.parent = &root;
    n1.left = &n2;
    n1.right = &n3;
    n1.para = (int *)&n1_para;

    n2.parent = &n1;
    n2.left = NULL;
    n2.right = NULL;
    n2.para = (int *)&n2_para;

    n3.parent = &n1;
    n3.left = &n4;
    n3.right = NULL;
    n3.para = (int *)&n3_para;

    n4.parent = &n3;
    n4.left = NULL;
    n4.right = NULL;
    n4.para = (int *)&n4_para;

    n5.parent = &root;
    n5.left = NULL;
    n5.right = &n6;
    n5.para = (int *)&n5_para;

    n6.parent = &n5;
    n6.left = NULL;
    n6.right = NULL;
    n6.para = (int *)&n6_para;

    printf("root address: %p\n", &root);
    printf("n1 address: %p\n", &n1);
    printf("n2 address: %p\n", &n2);
    printf("n3 address: %p\n", &n3);
    printf("n4 address: %p\n", &n4);
    printf("n5 address: %p\n", &n5);
    printf("n6 address: %p\n", &n6);

    // recursive
    printf("Using recursive method\n");
    search(&root);

    // iterative macro
    printf("Using recursive Morris transversal\n");
    // MorrisTraversal(&root);

    tree_node_t *temp_tree_node;
    ITERATE_TREE_BEGIN(&root, temp_tree_node) {
        printf("node-> %p, value: %d\n", temp_tree_node, *((int *)temp_tree_node->para));
    } ITERATE_TREE_END;

    printf("end\n");
    return 0;
}
