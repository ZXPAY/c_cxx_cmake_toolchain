#include <stdio.h>
#include "dblinklist.h"


void register_dblinklist(dbnode_t *head_p, dbnode_t *node_p, void *para) {
    dbnode_t *temp_node = head_p;
    while(temp_node->right != NULL) {
        temp_node = temp_node->right;
    }
    // Register a new node
    temp_node->right = node_p;
    temp_node->right->para = para;
}
