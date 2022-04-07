
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef enum _rbtree_color_em {
    RBTREE_RED = 0,
    RBTREE_BLACK = 1,
} rbtree_color_em;

typedef struct _redblack_tree_t {
    struct _redblack_tree_t *parent;
    struct _redblack_tree_t *left;
    struct _redblack_tree_t *right;
    rbtree_color_em color;
    int val;
} redblack_tree_t;

int test_array[] = {
    66, 78, 27, 35, 6, 2, 44, 58, 29, 76
};
#define ARRAY_SIZE  sizeof(test_array) / sizeof(int)

redblack_tree_t *generate_node(int val, rbtree_color_em color) {
    redblack_tree_t *node = malloc(sizeof(redblack_tree_t));
    memset(node, 0, sizeof(redblack_tree_t));
    node->val = val;
    node->color = color;
    return node;
}

redblack_tree_t *add_help(redblack_tree_t *node, redblack_tree_t *new_node) {
    if(node == NULL) {
        return new_node;
    }
    
    if(new_node->val == node->val) {
        assert(0);
    }
    else if(new_node->val < node->val) {
        // left
        redblack_tree_t *node_child = add_help(node->left, new_node);
        if(node->left != node_child) {
            // update
            node->left = node_child;
            node->left->parent = node;
        }
    }
    else if(new_node->val > node->val) {
        // right
        redblack_tree_t *node_child = add_help(node->right, new_node);
        if(node->right != node_child) {
            // update
            node->right = node_child;
            node->right->parent = node;
        }
    }

    return node;
}

redblack_tree_t *add_node(redblack_tree_t *root, int val) {
    redblack_tree_t *node = generate_node(val, RBTREE_RED);

    redblack_tree_t *root_after_add = add_help(root, node);
    if(root != root_after_add) {
        // update root
        root = root_after_add;
    }

    return root;
}

redblack_tree_t *build_tree(int *nums, int num_size) {
    redblack_tree_t *root = NULL;
    for(int i=0;i<num_size;i++) {
        root = add_node(root, nums[i]);
    }

    return root;
}


int main() {
    printf("Build tree\n");
    redblack_tree_t *root = build_tree(test_array, ARRAY_SIZE);

    printf("Root: %p, %d\n", root, root->val);


    printf("end\n");
}

