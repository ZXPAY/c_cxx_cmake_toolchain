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

struct TreeNode *searchBST(struct TreeNode *root, int val) {
    if(root == NULL) return NULL;

    if(root->val == val) {
        return root;
    }
    else if(val < root->val) {
        return searchBST(root->left, val);
    }
    else if(val > root->val) {
        return searchBST(root->right, val);
    }

    return NULL;
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

    struct TreeNode *root = generate_node(4);
    struct TreeNode *temp = root;

    temp->left = generate_node(2);
    temp->right = generate_node(7);

    temp = temp->left;
    temp->left = generate_node(1);
    temp->right = generate_node(3);

    struct TreeNode *result = searchBST(root, 2);

    printf("result: \n");
    print_preorder(result);
    printf("\n");

}

