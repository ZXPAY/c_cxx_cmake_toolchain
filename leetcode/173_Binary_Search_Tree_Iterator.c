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

typedef struct {
    struct TreeNode *cur;
    int count;
    int i_cur;
    int result[100000];
} BSTIterator;

void inorder_help(BSTIterator *obj, struct TreeNode *node) {
    if(node == NULL) return;

    inorder_help(obj, node->left);
    obj->result[obj->count++] = node->val;
    inorder_help(obj, node->right);
}

BSTIterator *bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator *obj = malloc(sizeof(BSTIterator));
    obj->cur = root;
    obj->count = 0;
    obj->i_cur = 0;

    inorder_help(obj, root);

    return obj;
}

int bSTIteratorNext(BSTIterator *obj) {
    if(obj->count <= obj->i_cur) return 0;
    return obj->result[obj->i_cur++];
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    if(obj->count > obj->i_cur) return true;
    return false;
}

void bSTIteratorFree(BSTIterator* obj) {
    free(obj);
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(7);
    root->left = generate_node(3);
    root->right = generate_node(15);
    root->right->left = generate_node(9);
    root->right->right = generate_node(20);

    BSTIterator* obj = bSTIteratorCreate(root);

    int *result = malloc(5*sizeof(int));
    memset(result, 0, 5*sizeof(int));
    bool *hash_next = malloc(5*sizeof(bool));

    for(int i=0;i<5;i++) {
        result[i] = bSTIteratorNext(obj);
        hash_next[i] = bSTIteratorHasNext(obj);
    }

    // print result
    for(int i=0;i<5;i++) {
        printf("%2d, %d\n", result[i], hash_next[i]);
    }
    
 
    bSTIteratorFree(obj);

}

