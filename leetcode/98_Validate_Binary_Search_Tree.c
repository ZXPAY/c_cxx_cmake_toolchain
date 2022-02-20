#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} tree_node_t;

// int test_array[] = {
//     5, 1, 4, 0, 0, 3 ,6
// };
int test_array[] = {
    2, 1, 3
};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

void print_tree_preorder(tree_node_t *node) {
    if(node == NULL) return;

    printf("print: %p, %d\n", node, node->val);
    print_tree_preorder(node->left);
    print_tree_preorder(node->right);
}

tree_node_t *bst_find_min(tree_node_t *node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

tree_node_t *bst_find_max(tree_node_t *node) {
    while(node->right != NULL) {
        node = node->right;
    }
    return node;
}

bool is_valid_bst_h(tree_node_t *node) {
    if(node == NULL) return true;

    bool result = true;

    // main logic
    if(node->left != NULL) {
        tree_node_t *max_node = bst_find_max(node->left);
        if(max_node->val >= node->val) {
            result = false;
        }
    }
    if(node->right != NULL) {
        tree_node_t *min_node = bst_find_min(node->right);
        if(min_node->val <= node->val) {
            result = false;
        }
    }

    // data flow
    bool result_left = is_valid_bst_h(node->left);
    if(result_left == false) result = false;
    bool result_right = is_valid_bst_h(node->right);
    if(result_right == false) result = false;

    return result;
}

bool isValidBST(struct TreeNode* root) {
    if(root == NULL) return true;
    return is_valid_bst_h(root);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    /* Build the tree */
    tree_node_t *node[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i++) {
        if(test_array[i] == 0) {
            node[i] = NULL;
            continue;
        }
        node[i] = (tree_node_t *)malloc(sizeof(tree_node_t));
        node[i]->left = NULL;
        node[i]->right = NULL;
        node[i]->val = test_array[i];
    }

    tree_node_t *root = node[0];

    for(int i=0;i<ARRAY_SIZE-1;i++) {
        int i_left = (i + 1) * 2 - 1; 
        int i_right = (i + 1) * 2; 

        if(test_array[i] == 0) continue;

        tree_node_t *temp = node[i];

        if(i_left < ARRAY_SIZE) {
            temp->left = node[i_left];            
        }
        if(i_right < ARRAY_SIZE) {
            temp->right = node[i_right];   
        }

    }

    print_tree_preorder(root);
    printf("%d\n", isValidBST(root));
}

