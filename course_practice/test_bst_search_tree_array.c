#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
                5
        2               6
    1       4       X       7
   X X     3 X     X X     X  X

*/

void build_tree(int *nums, int *bst, int length);
void build_tree_help(int *nums, int *bst, int val, int i_node, int length);
int bst_searchtree_search(int *bst, int val, int length);
int bst_searchtree_search_help(int *bst, int index, int val, int length);

int test_array[] = {
    5, 2, 6, 1, 4, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0 
};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

void build_tree(int *nums, int *bst, int length) {
    for(int i=0;i<length;i++) {
        if(nums[i] != 0)
            build_tree_help(nums, bst, nums[i], 0, length);
    }
}

void build_tree_help(int *nums, int *bst, int val, int i_node, int length) {
    if(i_node >= length) return;
    
    int i_left = (i_node + 1) * 2 - 1;
    int i_right = (i_node + 1) * 2;

    // printf("%d, %d\n", i_left, i_right);
    // Find the empty spot    
    if(bst[i_node] == -1) {
        // printf("feed: %d\n", val);
        bst[i_node] = val;
        return;
    }
    
    if(val == bst[i_node]) {
        assert(0);
    }
    else if(val < bst[i_node]) {
        build_tree_help(nums, bst, val, i_left, length);

    }
    else if(val > bst[i_node]) {
        build_tree_help(nums, bst, val, i_right, length);
    }

}


int bst_searchtree_search(int *bst, int val, int length) {
    return bst_searchtree_search_help(bst, 0, val, length);    
}

int bst_searchtree_search_help(int *bst, int index, int val, int length) {
    if(index >= length) return -1;

    if(val == bst[index]) {
        return val;
    }
    else if(val < bst[index]) {
        // go left search
        int i_left = (index + 1) * 2 - 1;
        bst_searchtree_search_help(bst, i_left, val, length);
    }
    else if(val > bst[index]) {
        int i_right = (index + 1) * 2;
        bst_searchtree_search_help(bst, i_right, val, length);
    }
}

int main() {
    printf("start\n");

    int bst_tree[ARRAY_SIZE];
    memset(bst_tree, -1, sizeof(bst_tree));
    build_tree(test_array, bst_tree, ARRAY_SIZE);

    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", bst_tree[i]);
    }
    printf("\n");

    printf("search 1: %d\n", bst_searchtree_search(bst_tree, 1, ARRAY_SIZE));
    printf("search 6: %d\n", bst_searchtree_search(bst_tree, 6, ARRAY_SIZE));
    printf("search 10: %d\n", bst_searchtree_search(bst_tree, 10, ARRAY_SIZE));

    return 0;
}

