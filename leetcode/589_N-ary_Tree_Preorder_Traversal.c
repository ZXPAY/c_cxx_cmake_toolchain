#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
            1
        3   2   4
       5 6
*/
// ans: {1, 3, 5, 6, 2, 4}

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

struct Node {
    int val;
    int numChildren;
    struct Node **children;
};

struct Node *generate_node(int val, int num_children) {
    struct Node *node = malloc(sizeof(struct Node));
    node->val = val;
    node->numChildren = num_children;
    if(num_children != 0)
        node->children = malloc(sizeof(struct Node *)*num_children);

    return node;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void preorder_help(struct Node *node, int *val, int *count) {
    if(node == NULL) return;

    printf("%d\n", node->val);
    val[(*count)++] = node->val;
    
    for(int i=0;i<node->numChildren;i++) {
        preorder_help(node->children[i], val, count);
    }
}
int *preorder(struct Node *root, int *returnSize) {
    *returnSize = 0;
    int *result = malloc(10000*sizeof(int));
    preorder_help(root, result, returnSize);

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    struct Node *root = generate_node(1, 3);
    root->children[0] = generate_node(3, 2);
    root->children[1] = generate_node(2, 0);
    root->children[2] = generate_node(4, 0);

    root->children[0]->children[0] = generate_node(5, 0);
    root->children[0]->children[1] = generate_node(6, 0);
    

    int return_sz = 0;
    int *result = preorder(root, &return_sz);
    printf("%p, %d\n", result, return_sz);

    printf("result: {");
    for(int i=0;i<return_sz;i++) {
        printf("%d, ", result[i]);
    }
    printf("}\n");

}

