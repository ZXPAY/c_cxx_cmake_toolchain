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

void bst_find_min(struct TreeNode *node, int *val, struct TreeNode **min_node) {
    if(node == NULL) return;
    
    if(*val > node->val) {
        *val = node->val;
        *min_node = node;
    }

    bst_find_min(node->left, val, min_node);
    bst_find_min(node->right, val, min_node);
}

void bst_find_max(struct TreeNode *node, int *val, struct TreeNode **max_node) {
    if(node == NULL) return;
    
    if(*val < node->val) {
        *val = node->val;
        *max_node = node;
    }

    bst_find_max(node->left, val, max_node);
    bst_find_max(node->right, val, max_node);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void recoverTree_h(struct TreeNode *node) {
    if(node == NULL) return;

    // main logic
    int val_l = node->val;
    struct TreeNode *temp_l = NULL;
    if(node->left != NULL) {
        bst_find_max(node->left, &val_l, &temp_l);
    }


    int val_r = node->val;
    struct TreeNode *temp_r = NULL;
    if(node->right != NULL) {
        bst_find_min(node->right, &val_r, &temp_r);
    }

    printf("%p, %p\n", temp_l, temp_r);

    if(temp_l != NULL && temp_r != NULL) {
        swap(&temp_l->val, &temp_r->val);
        return;
    }
    else if(temp_l != NULL) {
        swap(&node->val, &temp_l->val);
        return;
    }
    else if(temp_r != NULL) {
        swap(&node->val, &temp_r->val);
        return;
    }

    // data flow
    recoverTree_h(node->left);
    recoverTree_h(node->right);
}

void recoverTree(struct TreeNode* root) {
    recoverTree_h(root);
}

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    struct TreeNode *root = generate_node(2);
    root->left = generate_node(3);
    root->right = generate_node(1);

    printf("%d, %d, %d\n", root->val, root->left->val, root->right->val);
    recoverTree(root);
    printf("%d, %d, %d\n", root->val, root->left->val, root->right->val);


}

