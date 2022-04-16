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

void traverse_and_change_help(struct TreeNode *node, int *accumulate_val) {
    if(node == NULL) return;

    traverse_and_change_help(node->right, accumulate_val);
    (*accumulate_val) += node->val;
    printf("=> %d    %d\n", node->val, *accumulate_val);
    node->val = *accumulate_val;
    traverse_and_change_help(node->left, accumulate_val);

}


struct TreeNode *convertBST(struct TreeNode *root) {
    int temp_sum = 0;
    traverse_and_change_help(root, &temp_sum);

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


    struct TreeNode *root = generate_node(4);
    struct TreeNode *temp = root;

    temp->left = generate_node(1);
    temp->right = generate_node(6);

    temp->left->left = generate_node(0);
    temp->left->right = generate_node(2);
    temp->left->right->right = generate_node(3);

    temp->right->left = generate_node(5);
    temp->right->right = generate_node(7);
    temp->right->right->right = generate_node(8);


    struct TreeNode *result = convertBST(root);
    print_preorder(result);
    printf("\n");


}

