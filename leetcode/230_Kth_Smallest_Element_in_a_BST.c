#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void kthSmallest_help(struct TreeNode* node, int *k, int *result) {
    if(node == NULL) return;
    
    kthSmallest_help(node->left, k, result);
    printf("=> %d, %d\n", (*k), node->val);
    (*k)--;
    if(*k == 0) {
        *result = node->val;
        return;
    }
    kthSmallest_help(node->right, k, result);
}

int kthSmallest(struct TreeNode* root, int k) {
    int result = 0;
    kthSmallest_help(root, &k, &result);
    
    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(5);
    root->left = generate_node(3);
    root->left->left = generate_node(2);
    root->left->right = generate_node(4);
    root->left->left->left = generate_node(1);

    root->right = generate_node(6);

    printf("result: %d\n", kthSmallest(root, 3));


}

