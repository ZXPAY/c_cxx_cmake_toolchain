#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.
*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int minDepth(struct TreeNode *root){
    if(root == NULL) return 0;
    int l = minDepth(root->left);
    int r = minDepth(root->right);
    printf("%d, %d\n", l, r);
    if(l == 0 || r == 0) return 1 + l + r;
    return 1 + (l > r ? r : l);
}

int main() {
    printf("start\n");

    struct TreeNode head = {
        .left = NULL,
        .right = NULL,
        .val = 0,
    };

    struct TreeNode node1 = {
        .left = NULL,
        .right = NULL,
        .val = 1,
    };

    struct TreeNode node2 = {
        .left = NULL,
        .right = NULL,
        .val = 2,
    };

    struct TreeNode node3 = {
        .left = NULL,
        .right = NULL,
        .val = 3,
    };

    struct TreeNode node4 = {
        .left = NULL,
        .right = NULL,
        .val = 4,
    };

    struct TreeNode node5 = {
        .left = NULL,
        .right = NULL,
        .val = 5,
    };

    // struct TreeNode node6 = {
    //     .left = NULL,
    //     .right = NULL,
    //     .val = 6,
    // };

    head.left = &node1;
    node1.left = &node5;
    head.right = &node2;
    node2.left = &node3;
    node2.right = &node4;


    printf("minDepth: %d\n", minDepth(&head));

}
