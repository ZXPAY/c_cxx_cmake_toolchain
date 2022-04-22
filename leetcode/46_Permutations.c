#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_nums[] = {1, 2, 3};
#define ARRAY_SIZE (sizeof(test_nums) / sizeof(int))


/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


void permute_help(int **result, int *nums, int numsSize, int *buf, int i_buf, int index) {
    
    for(int i=0;i<i_buf;i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    for(int i=0;i<numsSize;i++) {
        bool fg = false;
        for(int j=0;j<i_buf;j++) {
            if(nums[i] == buf[j]) fg = true;
        }
        if(fg) continue;
        buf[i_buf++] = nums[i];
        permute_help(result, nums, numsSize, buf, i_buf, index+1);
        i_buf--;
    }

}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int **result = malloc(sizeof(int *)*numsSize*(numsSize-1));
    for(int i=0;i<(numsSize*(numsSize-1));i++) {
        result[i] = malloc(sizeof(int)*numsSize);
    }

    int *return_col = malloc(sizeof(int)*numsSize*(numsSize-1));
    for(int i=0;i<numsSize*(numsSize-1);i++) return_col[i] = numsSize;
    *returnColumnSizes = return_col;
    *returnSize = numsSize*(numsSize-1);

    int *buf = malloc(3*sizeof(int));
    int i_buf = 0;

    permute_help(result, nums, numsSize, buf, i_buf, 0);

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int return_size = 0;
    int *return_col_size;
    int **result = permute(test_nums, ARRAY_SIZE, &return_size, &return_col_size);
    for(int i=0;i<return_size;i++) {
        printf("{");
        for(int j=0;j<return_col_size[i];j++) {
            printf("%d, ", result[i][j]);
        }
        printf("}\n");
    }


}

