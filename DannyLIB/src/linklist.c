#include <stdio.h>
#include "linklist.h"


void register_linklist(node_t *head_p, node_t *node_p, void *para) {
    node_t *temp_node = head_p;
    while(temp_node->next != NULL) {
        temp_node = temp_node->next;
    }
    // Register a new node
    temp_node->next = node_p;
    temp_node->next->para = para;
}

