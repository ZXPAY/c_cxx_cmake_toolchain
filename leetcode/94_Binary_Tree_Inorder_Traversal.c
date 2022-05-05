#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} tree_node_t;

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void inorder_help(struct TreeNode *node, int *result, int *i_res) {
    if(node == NULL) return;
    
    inorder_help(node->left, result, i_res);
    result[(*i_res)++] = node->val;
    inorder_help(node->right, result, i_res);
}

int *inorderTraversal(struct TreeNode* root, int *returnSize){
    int *result = malloc(100*sizeof(int));
    *returnSize = 0;
    inorder_help(root, result, returnSize);
    
    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(7);
    root->left = generate_node(3);
    root->right = generate_node(15);
    root->right->left = generate_node(9);
    root->right->right = generate_node(20);

    int return_sz;
    int *result = inorderTraversal(root, &return_sz);
    for(int i=0;i<return_sz;i++) {
        printf("%d,", result[i]);
    }
    printf("\n");
}

