
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

typedef enum _rbtree_side_em {
    RBTREE_NONE = -1,
    RBTREE_LEFT = 0,
    RBTREE_RIGHT = 1,
} rbtree_side_em;

typedef struct _redblack_tree_t {
    struct _redblack_tree_t *parent;
    struct _redblack_tree_t *left;
    struct _redblack_tree_t *right;
    rbtree_color_em color;
    int val;
} redblack_tree_t;

int test_array[] = {
    50, 37, 25, 18, 22, 31, 34, 33
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

bool is_red(redblack_tree_t *node) {
    if(node != NULL && node->color == RBTREE_RED) return true;
    return false;
}

bool is_black(redblack_tree_t *node) {
    if(node == NULL || node->color == RBTREE_BLACK) return true;
    return false;
}

rbtree_side_em get_deeper_side(redblack_tree_t *node) {
    rbtree_side_em deeper_side = RBTREE_NONE;
    if(node->parent->parent->left == node->parent) {
        deeper_side = RBTREE_LEFT;
    }
    else if(node->parent->parent->right == node->parent) {
        deeper_side = RBTREE_RIGHT;
    }

    assert(deeper_side!=RBTREE_NONE);
    return deeper_side;
}

redblack_tree_t *get_uncle(redblack_tree_t *node) {
    rbtree_side_em side = get_deeper_side(node);
    if(RBTREE_LEFT == side) {
        return node->parent->parent->right;
    }
    else if(RBTREE_RIGHT == side) {
        return node->parent->parent->left;
    }
    assert(0);
    return NULL;
}

redblack_tree_t *rotate_left(redblack_tree_t *node) {
    redblack_tree_t *root_old = node; // new node's grandpa
    redblack_tree_t *root_old_parent = node->parent; // probable the root
    redblack_tree_t *root_new = node->right;
    redblack_tree_t *subtree = node->right->left;

    root_old->right = subtree;
    if(subtree != NULL) {
        subtree->parent = root_old;
    }
    root_old->parent = root_new;
    root_new->left = root_old;

    root_new->parent = root_old_parent;
    if(root_old_parent != NULL) {
        if(root_old_parent->left == root_old) {
            root_old_parent->left = root_new;
        }
        else if(root_old_parent->right == root_old) {
            root_old_parent->right = root_new;
        }
    }

    return root_new;
}

redblack_tree_t *rotate_right(redblack_tree_t *node) {
    redblack_tree_t *root_old = node; // new node's grandpa
    redblack_tree_t *root_old_parent = node->parent; // probable the root
    redblack_tree_t *root_new = node->left;
    redblack_tree_t *subtree = node->left->right;

    root_old->left = subtree;
    if(subtree != NULL) {
        subtree->parent = root_old;
    }
    root_old->parent = root_new;
    root_new->right = root_old;

    root_new->parent = root_old_parent;
    if(root_old_parent != NULL) {
        if(root_old_parent->left == root_old) {
            root_old_parent->left = root_new;
        }
        else if(root_old_parent->right == root_old) {
            root_old_parent->right = root_new;
        }
    }

    return root_new;
}

void balanceA1(redblack_tree_t **root, redblack_tree_t *node) {
    // move color up
    node->parent->color = RBTREE_BLACK;
    node->parent->parent->color = RBTREE_RED;

    // rotate
    redblack_tree_t *node_grandparent_before = node->parent->parent;
    redblack_tree_t *node_grandparent_after = NULL;
    rbtree_side_em side = get_deeper_side(node);
    if(RBTREE_LEFT == side) {
        node_grandparent_after = rotate_right(node->parent->parent);
    }
    else if(RBTREE_RIGHT == side) {
        node_grandparent_after = rotate_left(node->parent->parent);
    }
    if((*root) == node_grandparent_before) {
        *root = node_grandparent_after;
    }
} 

void balanceA2(redblack_tree_t **root, redblack_tree_t *node) {
    rbtree_side_em side = get_deeper_side(node);
    if(RBTREE_LEFT == side) {
        rotate_left(node->parent);   // small scale rotate
        balanceA1(root, node->left);
    }
    else if(RBTREE_RIGHT == side) {
        rotate_right(node->parent);   // small scale rotate
        balanceA1(root, node->right);
    }
} 

redblack_tree_t *balanceB(redblack_tree_t *node) {
    // move color up
    redblack_tree_t *uncle = get_uncle(node);
    uncle->color = RBTREE_BLACK;
    node->parent->color = RBTREE_BLACK;
    node->parent->parent->color = RBTREE_RED;

    return node->parent->parent;
}

void balance(redblack_tree_t **root, redblack_tree_t *node) {
    // first case
    if(node == (*root)) {
        printf("===== Insert case root =====\n");
        node->color = RBTREE_BLACK;
        return;
    }
    // if parent is red
    if(is_red(node->parent)) {
        // two red node next to each other
        rbtree_side_em side = get_deeper_side(node);
        redblack_tree_t *uncle = get_uncle(node);


        if(is_black(uncle)) {
            if(RBTREE_LEFT == side) {
                if(node->parent->left == node) {
                    printf("===== Insert case A1 (right rotation) =====\n");
                    balanceA1(root, node);
                }
                else if(node->parent->right == node) {
                    printf("===== Insert case A2 (left-right rotation) =====\n");
                    balanceA2(root, node);
                }
            }
            else if(RBTREE_RIGHT == side) {
                if(node->parent->right == node) {
                    printf("===== Insert case A1 (left rotation) =====\n");
                    balanceA1(root, node);
                }
                else if(node->parent->left == node) {
                    printf("===== Insert case A2 (right-left rotation) =====\n");
                    balanceA2(root, node);
                }
            }
        }
        else if(is_red(uncle)) {
            printf("===== Insert case B =====\n");
            redblack_tree_t *node_next_round = balanceB(node);
            balance(root, node_next_round);
        }
    }
    else {
        printf("parent is black, ok, pass balance\n");
    }
}

redblack_tree_t *add_node(redblack_tree_t *root, int val) {
    redblack_tree_t *node = generate_node(val, RBTREE_RED);
    printf("generate node[%p]: %d\n", node, node->val);

    redblack_tree_t *root_after_add = add_help(root, node);
    if(root != root_after_add) {
        // update root
        root = root_after_add;
    }

    // Red Black tree balance
    balance(&root, node);

    return root;
}

redblack_tree_t *get_sibling(redblack_tree_t *node) {
    if(node->parent != NULL) {
        if(node->parent->right == node) {
            return node->parent->left;
        }
        else if(node->parent->left == node) {
            return node->parent->right;
        }
    }

    return NULL;
}

redblack_tree_t *get_sibling_near_child(redblack_tree_t *node) {
    if(node->parent != NULL) {
        if(node->parent->right == node) {
            if(node->parent->left != NULL) {
                return node->parent->left->right;
            }
        }
        else if(node->parent->left == node) {
            if(node->parent->right != NULL) {
                return node->parent->right->left;
            }
        }
    }

    return NULL;
}

redblack_tree_t *get_sibling_far_child(redblack_tree_t *node) {
    if(node->parent != NULL) {
        if(node->parent->right == node) {
            if(node->parent->left != NULL) {
                return node->parent->left->left;
            }
        }
        else if(node->parent->left == node) {
            if(node->parent->right != NULL) {
                return node->parent->right->right;
            }
        }
    }

    return NULL;
}

void rotate_delete(redblack_tree_t **root, redblack_tree_t *node, redblack_tree_t *node_to_rotate) {
    if(node_to_rotate == node->parent) {
        redblack_tree_t *parent_before_rotate = node->parent;
        redblack_tree_t *parent_after_rotate = NULL;
        if(node->parent->left == node) {
            parent_after_rotate = rotate_left(node->parent);
        }
        else if(node->parent->right == node) {
            parent_after_rotate = rotate_right(node->parent);
        }
        if((*root) == parent_before_rotate) {
            *root = parent_after_rotate;
        }
    }
    else if(node_to_rotate == get_sibling(node)) {
        redblack_tree_t *sibling = get_sibling(node);
        redblack_tree_t *sibling_near_child = get_sibling_near_child(node);
        if(sibling->left == sibling_near_child) {
            rotate_right(sibling);
        }
        else if(sibling->right == sibling_near_child) {
            rotate_left(sibling);
        }
    }
}

void balance_before_delete(redblack_tree_t **root, redblack_tree_t *node) {
    redblack_tree_t *parent = node->parent;
    redblack_tree_t *sibling = get_sibling(node);
    redblack_tree_t *sibling_near_child = get_sibling_near_child(node);
    redblack_tree_t *sibling_far_child = get_sibling_far_child(node);

    if(is_red(node)){
        printf("===== Delete Type A =====\n");
        return;
    }
    
    if(node == (*root)) {
        printf("===== Delete Type B =====\n");
        node->color = RBTREE_BLACK;
        return;
    }

    if(is_red(sibling)) {
        printf("===== Delete Type C - Case 1 =====\n");
        sibling->color = RBTREE_BLACK;
        parent->color = RBTREE_RED;
        rotate_delete(root, node, parent);
        balance_before_delete(root, node);  // go to next round
        return;
    }

    if(is_black(sibling)) {
        if(is_black(sibling_near_child) && is_black(sibling_far_child)) {
            if(is_red(parent)) {
                printf("===== Delete Type C - Case 2.1 =====\n");
                sibling->color = RBTREE_RED;
                parent->color = RBTREE_BLACK;
            }
            else if(is_black(parent)) {
                printf("===== Delete Type C - Case 2.2 =====\n");
                sibling->color = RBTREE_RED;
                balance_before_delete(root, parent); // go to next round
            }
        }
        else if(is_black(sibling_far_child) && is_red(sibling_near_child)) {
            printf("===== Delete Type C - Case 3 =====\n");
            sibling_near_child->color = RBTREE_BLACK;
            sibling->color = RBTREE_RED;
            rotate_delete(root, node, sibling);
            balance_before_delete(root, node); // go to next round (Case 4)
        }
        else if(is_red(sibling_far_child)) {
            if(is_black(parent)) {
                printf("===== Delete Type C - Case 4.1 =====\n");
                rotate_delete(root, node, parent);
                sibling_far_child->color = RBTREE_BLACK;
            }
            else if(is_red(parent)) {
                printf("===== Delete Type C - Case 4.2 =====\n");
                parent->color = RBTREE_BLACK;
                sibling->color = RBTREE_RED;
                rotate_delete(root, node, parent);
                // printf("%d, %d\n", (*root)->right->val);
                sibling_far_child->color = RBTREE_BLACK;
            }
        }
    }

}

redblack_tree_t *get_min_node(redblack_tree_t *node) {
    if(node == NULL) return NULL;
    while(node->left != NULL) node = node->left;

    return node;
}

redblack_tree_t *get_max_node(redblack_tree_t *node) {
    if(node == NULL) return NULL;
    while(node->right != NULL) node = node->right;

    return node;
}

void swap_node_value(redblack_tree_t *node1, redblack_tree_t *node2) {
    assert(node1 != NULL);
    assert(node2 != NULL);
    int temp = node1->val;
    node1->val = node2->val;
    node2->val = temp;
}

void delete_help2(redblack_tree_t **root, redblack_tree_t *node) {
    if(node == (*root)) {
        *root = NULL;
    }
    else if(node->parent->right == node) {
        // free(node->parent->right);
        node->parent->right = NULL;
    }
    else if(node->parent->left == node) {
        // free(node->parent->left);
        node->parent->left = NULL;
    }
}

void delete_help(redblack_tree_t **root, redblack_tree_t *node, int val) {
    if(node == NULL) return;

    // find the value, delete it
    if(val == node->val) {
        // it's leaf node
        if(node->left == NULL && node->right == NULL) {
            balance_before_delete(root, node);
            delete_help2(root, node);
        }
        // swap value and go to leaf node
        else if(node->left == NULL && node->right != NULL) {
            redblack_tree_t *node_min = get_min_node(node->right);
            swap_node_value(node, node_min);
            delete_help(root, node_min, val);
        }
        else if(node->left != NULL && node->right == NULL) {
            redblack_tree_t *node_max = get_max_node(node->left);
            swap_node_value(node, node_max);
            delete_help(root, node_max, val);
        }
        else if(node->left != NULL && node->right != NULL) {
            // choose left or right
            redblack_tree_t *node_min = get_min_node(node->right);
            swap_node_value(node, node_min);
            delete_help(root, node_min, val);
        }
    }
    else if(val < node->val) {
        delete_help(root, node->left, val);
    }
    else if(val > node->val) {
        delete_help(root, node->right, val);
    }
}

redblack_tree_t *delete(redblack_tree_t *root, int val) {
    if(root == NULL) return NULL;
    delete_help(&root, root, val);

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

    printf("==================== Delete ====================\n");


    root = delete(root, 50);  // Type 4.2
    root = delete(root, 37);  // Type 2.1
    root = delete(root, 34);  // Type A (BST delete)
    root = delete(root, 33);  // Type C - 1
    root = delete(root, 18);  // Type C - 3
    root = delete(root, 31);  // Type C - 2.2
    root = delete(root, 22);  // Type A
    root = delete(root, 25);  // Type B


    printf("end\n");
}

