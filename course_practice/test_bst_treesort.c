#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
                5
        2               6
    1       4       X       7
   X X     3 X     X X     X  X

*/

typedef struct _dblinklist_t {
    struct _dblinklist_t *left;
    struct _dblinklist_t *right;
    int val;
} dblinklist_t;

dblinklist_t *build_tree(int *nums, int length);
dblinklist_t *bst_searchtree_add(dblinklist_t *node, int val);


// int test_array[] = {
//     5, 2, 6, 1, 4, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0 
// };

int test_array[] = {
    5, 6, 7, 2, 1, 6, 2
};

#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

dblinklist_t *build_tree(int *nums, int length) {
    dblinklist_t *root = NULL;

    for(int i=0;i<length;i++) {
        dblinklist_t *temp = bst_searchtree_add(root, nums[i]);

        if(root != temp) {
            root = temp;
            printf("root: %p, %d\n", root, nums[i]);
        }

    }

    return root;
}

dblinklist_t *bst_searchtree_add(dblinklist_t *node, int val) {
    if(node == NULL) {
        node = (dblinklist_t *)malloc(sizeof(dblinklist_t));
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
        dblinklist_t *tmp = bst_searchtree_add(node->left, val);
        if(tmp != node->left) {
            printf("left: %p, %d\n", tmp, val);
            node->left = tmp;
        }
    }
    else if(node->val < val) {   // Go right
        dblinklist_t *tmp = bst_searchtree_add(node->right, val);
        if(tmp != node->right) {
            printf("right: %p, %d\n", tmp, val);
            node->right = tmp;
        }
    }

    return node;
}

dblinklist_t *bst_searchtree_search(dblinklist_t *node, int val) {
    if(node == NULL) return NULL;
    if(node->val == val) {
        return node;
    }
    else if(node->val > val) {
        bst_searchtree_search(node->left, val);
    }
    else if(node->val < val) {
        bst_searchtree_search(node->right, val);
    }
    else {
        return NULL;
    }
}

dblinklist_t *get_min(dblinklist_t *node) {
    dblinklist_t *tmp = node;
    while(true) {
        if(tmp->left == NULL) {
            break;
        }
        tmp = tmp->left;
    }
    return tmp;
}

void swap_node_value(dblinklist_t *node1, dblinklist_t *node2) {
    int tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
}

dblinklist_t *bst_searchtree_delete_help(dblinklist_t **node, int val, dblinklist_t **delete_node) {
    if(*node == NULL) return NULL;

    if((*node)->val == val) {
        // X X
        if((*node)->left == NULL && (*node)->right == NULL) {
            *delete_node = *node;
            *node = NULL;
            return (*node);
        }
        // X V
        else if((*node)->left == NULL && (*node)->right != NULL) {
            *delete_node = *node;
            node = &(*node)->right;
            return (*node);
        }
        // V X
        else if((*node)->left != NULL && (*node)->right == NULL) {
            *delete_node = *node;
            *node = (*node)->left;

            return *node;
        }
        // V V
        else if((*node)->left != NULL && (*node)->right != NULL) {
            // Step1: swap the delete node and min(right tree)
            dblinklist_t *min_node = get_min((*node)->right);
            swap_node_value((*node), min_node);   // the same memory
            // Step2: delete recursive again
            dblinklist_t *tmp_node = bst_searchtree_delete_help(&(*node)->right, val, delete_node);
            if((*node)->right != tmp_node) {
                (*node)->right = tmp_node;
            }
        }
    }
    else if((*node)->val > val) {
        dblinklist_t *node_child = bst_searchtree_delete_help(&(*node)->left, val, delete_node);
        if((*node)->left != node_child) {
            (*node)->left = node_child;
        }
    }
    else if((*node)->val < val) {
        dblinklist_t *node_child = bst_searchtree_delete_help(&(*node)->right, val, delete_node);
        if((*node)->right != node_child) {
            (*node)->right = node_child;
        }
    }

    return (*node);
}

void bst_searchtree_delete(dblinklist_t *node, int val) {
    if(node == NULL) return;

    dblinklist_t **delete_node = malloc(sizeof(dblinklist_t **));
    bst_searchtree_delete_help(&node, val, delete_node);

    printf("delete node: %p\n", *delete_node);

    // free the delete node
    free(*delete_node);
    free(delete_node);
}

void print_tree_preorder(dblinklist_t *node) {
    if(node == NULL) return;

    printf("print: %d\n", node->val);
    print_tree_preorder(node->left);
    print_tree_preorder(node->right);
}


void print_tree_inorder(dblinklist_t *node) {
    if(node == NULL) return;

    print_tree_inorder(node->left);
    printf("%d, ", node->val);
    print_tree_inorder(node->right);
}

void print_tree_inorder_right(dblinklist_t *node) {
    if(node == NULL) return;

    print_tree_inorder_right(node->right);
    printf("%d, ", node->val);
    print_tree_inorder_right(node->left);
}

int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");


    dblinklist_t *root = build_tree(test_array, ARRAY_SIZE);

    printf("print tree inorder (left), min -> max\n");
    print_tree_inorder(root);
    printf("\n");

    printf("print tree inorder (right), max -> min\n");
    print_tree_inorder_right(root);
    printf("\n");
    
    return 0;
}


