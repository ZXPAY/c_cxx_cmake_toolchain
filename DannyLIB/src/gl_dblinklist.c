#include <stdlib.h>
#include "gl_dblinklist.h"

void insert_gllinklist(gl_node_t *node1_p, gl_node_t *node2_p) {
    if(NULL == node1_p || NULL == node2_p) return;
    node1_p->right = node2_p;
    node2_p->left = node1_p;
}
