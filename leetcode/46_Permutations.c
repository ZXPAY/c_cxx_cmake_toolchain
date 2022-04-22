#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_nums[] = {1, 2, 3, 4};
// int test_nums[] = {1};
#define ARRAY_SIZE (sizeof(test_nums) / sizeof(int))


/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute_help(int **result, int *i_result, int *nums, int numsSize, int l, int r) {
    if(l == r) {
        for(int i=0;i<numsSize;i++) {
            printf("%d, ", nums[i]);
        }
        printf("\n");
        memcpy(result[(*i_result)++], nums, numsSize*sizeof(int));
    }
    else {
        for(int i=l;i<=r;i++) {
            swap(&nums[l], &nums[i]);
            permute_help(result, i_result, nums, numsSize, l+1, r);
            swap(&nums[l], &nums[i]);
        }
    }    
}


int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int permute_size = 1;
    for(int i=numsSize;i>=1;i--) {
        permute_size *= i;
    }
    int **result = malloc(sizeof(int *)*permute_size);
    for(int i=0;i<(permute_size);i++) {
        result[i] = malloc(sizeof(int)*numsSize);
    }

    int *return_col = malloc(sizeof(int)*permute_size);
    for(int i=0;i<permute_size;i++) return_col[i] = numsSize;
    *returnColumnSizes = return_col;

    int i_result = 0;
    permute_help(result, &i_result, nums, numsSize, 0, numsSize-1);
    *returnSize = i_result;

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

