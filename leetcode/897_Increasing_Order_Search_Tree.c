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

void increasingBST_help(struct TreeNode* root, struct TreeNode **res_root, struct TreeNode **node) {
    if(root == NULL) return;

    increasingBST_help(root->left, res_root, node);    

    printf("%d\n", root->val);
    if(*res_root == NULL) {
        *node = generate_node(root->val);
        *res_root = *node;
    }
    else {
        (*node)->right = generate_node(root->val);
        *node = (*node)->right;
    }

    increasingBST_help(root->right, res_root, node);    
}
struct TreeNode *increasingBST(struct TreeNode* root) {
    struct TreeNode *result = NULL;
    struct TreeNode *node = NULL;

    increasingBST_help(root, &result, &node);

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
    root->right->right = generate_node(8);
    root->right->right->left = generate_node(7);
    root->right->right->right = generate_node(9);


    struct TreeNode *result = increasingBST(root);
    struct TreeNode *temp = result;

    printf("result:\n");
    while(temp != NULL) {
        printf("%d\n", temp->val);
        temp = temp->right;
    }


}

