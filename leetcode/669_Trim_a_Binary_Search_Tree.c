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


struct TreeNode *trimBST(struct TreeNode *root, int low, int high) {
    if(NULL == root) return NULL;

    if(root->val < low) {
        // Go right, pass this node
        return trimBST(root->right, low, high);
    }
    else if(root->val > high) {
        // Go left, pass this node
        return trimBST(root->left, low, high);
    }
    
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);

    return root;
}

void print_preorder(struct TreeNode *node) {
    if(node == NULL) return;

    printf("%d, ", node->val);
    print_preorder(node->left);    
    print_preorder(node->right);    
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(3);
    struct TreeNode *temp = root;

    temp->left = generate_node(0);
    temp->right = generate_node(4);

    temp = temp->left;
    temp->right = generate_node(2);

    temp = temp->right;
    temp->left = generate_node(1);

    struct TreeNode *result = trimBST(root, 1, 3);
    // answer:
    //        3
    //       /
    //      2
    //     /
    //    1

    print_preorder(result);
    printf("\n");




}

