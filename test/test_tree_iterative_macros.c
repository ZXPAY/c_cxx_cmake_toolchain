#include <stdio.h>
#include "linklist.h"


int main(void) {
    printf("start testing\n");

    node_t n_head = {.next = NULL, .para = NULL};

    char n1_para[] = "I am node 1.";
    node_t n1 = {.next = NULL, .para = n1_para};

    char n2_para[] = "I am node 2.";
    node_t n2 = {.next = NULL, .para = n2_para};

    char n3_para[] = "I am node 3.";
    node_t n3 = {.next = NULL, .para = n3_para};

    // Link the all node
    register_linklist(&n_head, &n1, (char *)n1_para);
    register_linklist(&n_head, &n2, (char *)n2_para);
    register_linklist(&n_head, &n3, (char *)n3_para);

    node_t *temp_node = NULL;
    printf("iterate the linklist\n");
    ITERATE_LINKLIST_BEGIN(&n_head, temp_node) {
        printf("%s\n", (char *)temp_node->para);
    } ITERATE_LINKLIST_END;
    printf("end of iteration\n");


    return 0;
}

