#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _dblinklist_t {
    struct _dblinklist_t *left;
    struct _dblinklist_t *right;
    int val;
} dblinklist_t;

dblinklist_t *build_tree(int *nums, int length);
dblinklist_t *bst_searchtree_add(dblinklist_t *node, int val);


/* right-right */
// int test_array[] = {
    // 3, 4, 5
// };

/* left-left */
// int test_array[] = {
    // 5, 4, 3
// };

/* left-right */
// int test_array[] = {
    // 5, 3, 4
// };

/* right-left */
// int test_array[] = {
//     3, 5, 4
// };

/* test */
int test_array[] = {
    100, 80, 60, 40, 20, 70
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

dblinklist_t *rotate_left(dblinklist_t *node) {
    assert(node!=NULL);
    assert(node->right!=NULL);
    dblinklist_t *node_old = node;
    dblinklist_t *node_new = node->right;
    dblinklist_t *node_sub = node->right->left;
    
    node_old->right = node_sub;
    node_new->left = node_old;
    
    return node_new;
}

dblinklist_t *rotate_right(dblinklist_t *node) {
    assert(node!=NULL);
    assert(node->left!=NULL);
    dblinklist_t *node_old = node;
    dblinklist_t *node_new = node->left;
    dblinklist_t *node_sub = node->left->right;
    node_old->left = node_sub;
    node_new->right = node_old;
    
    return node_new;
}

int get_depth(dblinklist_t *node) {
    if(node == NULL) return 0;
    int l_depth = 1 + get_depth(node->left);
    int r_depth = 1 + get_depth(node->right);

    if(l_depth > r_depth) return l_depth;
    return r_depth;
}

// return left depth - right depth
int get_depth_gap(dblinklist_t *node) {
    if(node == NULL) return 0;
    return get_depth(node->left) - get_depth(node->right);
}

dblinklist_t *balance_tree(dblinklist_t *node) {
    int depth_gap = get_depth_gap(node);
    if(depth_gap <= 1 && depth_gap >= -1) return node;

    if(depth_gap > 1) {
        // left is deeper
        dblinklist_t *node_left_result = balance_tree(node->left);
        if(node->left != node_left_result) {
            node->left = node_left_result;
        }
    }
    else if(depth_gap < -1) {
        // right is deeper
        dblinklist_t *node_right_result = balance_tree(node->right);
        if(node->right != node_right_result) {
            node->right = node_right_result;
        }
    }

    if(depth_gap > 1) {
        // left is deeper
        int depth_gap_nextlayer = get_depth_gap(node->left);
        if(depth_gap_nextlayer >= 0) {
            printf("left-left\n");
        }
        else {
            printf("left-right\n");
            dblinklist_t *node_left_result = rotate_left(node->left);
            if(node != node_left_result) {
                node->left = node_left_result;
            }
        }
        dblinklist_t *node_result = rotate_right(node);
        if(node != node_result) {
            node = node_result;
        }
    }
    else if(depth_gap < -1) {
        // left is deeper
        int depth_gap_nextlayer = get_depth_gap(node->right);
        if(depth_gap_nextlayer <= 0) {
            printf("right-right\n");
        }
        else {
            printf("right-left\n");
            dblinklist_t *node_right_result = rotate_right(node->right);
            if(node != node_right_result) {
                node->right = node_right_result;
            }
        }

        dblinklist_t *node_result = rotate_left(node);
        if(node != node_result) {
            node = node_result;
        }
    }
    return node;
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
    else if(node->val == val) {
        // In BST search tree should not happen
        assert(0);
    }
    else if(node->val > val) {   // Go left
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

    return balance_tree(node);
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
    return NULL;
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

    return balance_tree(*node);
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

int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");


    dblinklist_t *root = build_tree(test_array, ARRAY_SIZE);
    printf("Final root: %p\n", root);

    /* Use the test array {3, 4, 5} */
    // printf("%p, %p, %p\n", root, root->left, root->right);
    // root = rotate_left(root);
    // printf("%p, %p, %p\n", root, root->left, root->right);

    /* Use the test array {5, 4, 3} */
    // printf("%p, %p, %p\n", root, root->left, root->right);
    // root = rotate_right(root);
    // printf("%p, %p, %p\n", root, root->left, root->right);


    print_tree_preorder(root);
    printf("left-right depth = %d\n", get_depth_gap(root));
    
    bst_searchtree_delete(root, 80);
    print_tree_preorder(root);
    printf("left-right depth = %d\n", get_depth_gap(root));
    return 0;
}


