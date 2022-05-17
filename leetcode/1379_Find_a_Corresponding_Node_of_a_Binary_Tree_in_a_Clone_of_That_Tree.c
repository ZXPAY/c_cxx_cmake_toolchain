#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}


TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target) {
    if(original == NULL) return NULL;

    if(target == original) {
        return cloned;
    }

    TreeNode *result_left = getTargetCopy(original->left, cloned->left, target);
    if(result_left != NULL) {
        return result_left;
    }
    TreeNode *result_right = getTargetCopy(original->right, cloned->right, target);
    if(result_right != NULL) {
        return result_right;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    TreeNode *root1 = generate_node(7);
    root1->left = generate_node(4);
    root1->right = generate_node(3);
    root1->right->left = generate_node(6);
    root1->right->right = generate_node(19);

    TreeNode *root2 = generate_node(7);
    root2->left = generate_node(4);
    root2->right = generate_node(3);
    root2->right->left = generate_node(6);
    root2->right->right = generate_node(19);

    TreeNode *result = getTargetCopy(root1, root2, root1->right);
    printf("ans: %p, %d, get result: %p, %d\n", root2->right, root2->right->val, result, result->val);
}

