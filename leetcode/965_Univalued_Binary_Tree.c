#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
A binary tree is uni-valued if every node in the tree has the same value.

Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.
*/


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->val = val;

    return node;
}

void search_help(struct TreeNode *node, int value, bool *result) {
    if(node == NULL) return;

    if(node->val != value) {
        *result = false;
        return;
    }
    search_help(node->left, value, result);
    search_help(node->right, value, result);
}

bool isUnivalTree(struct TreeNode *root) {
    bool result = true;

    search_help(root, root->val, &result);
    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(1);
    root->left = generate_node(1);
    root->right = generate_node(1);

    root->left->left = generate_node(1);
    root->left->right = generate_node(1);

    root->right->left = generate_node(1);
    root->right->right = generate_node(1);

    printf("%d\n", isUnivalTree(root));
}

