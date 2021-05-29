#include <stdio.h>
#include "dblinklist.h"


int main(void) {
    printf("start testing\n");

    dbnode_t n_head = {.right = NULL, .para = NULL};

    char n1_para[] = "I am node 1.";
    dbnode_t n1 = {.left = &n_head, .right = NULL, .para = n1_para};

    char n2_para[] = "I am node 2.";
    dbnode_t n2 = {.left = &n1, .right = NULL, .para = n2_para};

    char n3_para[] = "I am node 3.";
    dbnode_t n3 = {.left = &n2, .right = NULL, .para = n3_para};

    // Link the all node
    register_dblinklist(&n_head, &n1, (char *)n1_para);
    register_dblinklist(&n_head, &n2, (char *)n2_para);
    register_dblinklist(&n_head, &n3, (char *)n3_para);

    dbnode_t *temp_node = NULL;
    printf("iterate the linklist\n");
    ITERATE_LINKLIST_BEGIN(&n_head, temp_node) {
        printf("%s\n", (char *)temp_node->para);
    } ITERATE_LINKLIST_END;
    printf("end of iteration\n");


    return 0;
}

