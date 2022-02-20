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

int test_array[] = {1, 0, 2, 2, 6, 6, 5, 3, 4, 4, 5};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} tree_node_t;

tree_node_t *build_tree(int *nums, int length);
tree_node_t *bst_searchtree_add(tree_node_t *node, int val);

tree_node_t *build_tree(int *nums, int length) {
    tree_node_t *root = NULL;

    for(int i=0;i<length;i++) {
        tree_node_t *temp = bst_searchtree_add(root, nums[i]);

        if(root != temp) {
            root = temp;
            printf("root: %p, %d\n", root, nums[i]);
        }

    }

    return root;
}

tree_node_t *bst_searchtree_add(tree_node_t *node, int val) {
    if(node == NULL) {
        node = (tree_node_t *)malloc(sizeof(tree_node_t));
        node->left = NULL;
        node->right = NULL;
        node->val = val;
        return node;
    }

    if(val == 0) {
        // In C, no NULL integer
    }
    // else if(node->val == val) {
        // In BST search tree should not happen
        // assert(0);
    // }
    else if(node->val >= val) {   // Go left
        tree_node_t *tmp = bst_searchtree_add(node->left, val);
        if(tmp != node->left) {
            printf("left: %p, %d\n", tmp, val);
            node->left = tmp;
        }
    }
    else if(node->val < val) {   // Go right
        tree_node_t *tmp = bst_searchtree_add(node->right, val);
        if(tmp != node->right) {
            printf("right: %p, %d\n", tmp, val);
            node->right = tmp;
        }
    }

    return node;
}

void find_mode_h(tree_node_t *node, int *count, int *count_max, int *prev, int *return_val, int *return_sz) {
    if(node == NULL) return;

    find_mode_h(node->left, count, count_max, prev, return_val, return_sz);

    if(*prev == -1) {
        *prev = node->val;
        *count = 1;
    }
    else if(*prev != node->val) {
        *count = 1;
        *prev = node->val;
    }
    else if(*prev == node->val) {
        (*count)++;
    }

    // update the count
    if(*count > *count_max) {
        *count_max = *count;
        *return_sz = 1;
        *return_val = *prev;
    }
    else if(*count == *count_max) {
        if(realloc(return_val, sizeof(int) * ((*return_sz)+1+sizeof(int))) == NULL) {
            assert(0);
        }
        *(return_val + (*return_sz)) = *prev;
        (*return_sz)++;
    }

    // printf("%d, %d, %d\n", *prev, node->val, *count);

    find_mode_h(node->right, count, count_max, prev, return_val, return_sz);
}

int *findMode(struct TreeNode *root, int *returnSize) {
    int count = 0;
    int count_max = 0;
    int prev = -1;
    int *return_val = malloc(sizeof(int)+sizeof(int));
    *returnSize = 0;

    find_mode_h(root, &count, &count_max, &prev, return_val, returnSize);

    printf("count max: %d\n", count_max);
    printf("return size: %d\n", *returnSize);

    return return_val;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    tree_node_t *root = build_tree(test_array, ARRAY_SIZE);
    int return_size;
    int *val = findMode(root, &return_size);

    for(int i=0;i<return_size;i++) {
        printf("find: %d\n", val[i]);
    }

}

