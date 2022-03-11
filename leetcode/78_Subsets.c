#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.
*/

int test_set[] = {1, 2, 3, 4};
#define TEST_ARRAYSIZE (sizeof(test_set) / sizeof(int))

#define MAX_SUBSET_SIZE 5000


void backtracking(int *nums, int **subsets, int *return_cols, int num_size, int *subset, int i_s, int index, int *i_hash) {

    *(subsets+(*i_hash)) = malloc(num_size*sizeof(int));
    memset(*(subsets+(*i_hash)), 0, num_size*sizeof(int));
    memcpy(*(subsets+(*i_hash)), subset, i_s*sizeof(int));
    *(return_cols+*i_hash) = i_s;
    (*i_hash)++;


    for(int i=index;i<num_size;i++) {
        subset[i_s++] = nums[i];
        backtracking(nums, subsets, return_cols, num_size, subset, i_s, i+1, i_hash);
        i_s--;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int **subsets_result = malloc(MAX_SUBSET_SIZE*sizeof(int));
    memset(subsets_result, 0, MAX_SUBSET_SIZE*sizeof(int));

    int *retcolsizes = malloc(MAX_SUBSET_SIZE * sizeof(int));
    memset(retcolsizes, 0, MAX_SUBSET_SIZE * sizeof(int));
    *returnColumnSizes = retcolsizes;


    // for loop find the all possible subset
    int *temp = malloc(sizeof(int)*numsSize);
    memset(temp, 0, sizeof(int)*numsSize);
    int i_hash = 0;
    backtracking(nums, subsets_result, retcolsizes, numsSize, temp, 0, 0, &i_hash);

    *returnSize = i_hash;

    return subsets_result;
}


int main(int argc, char *argv[]) {
    int return_size;
    
    int **return_cols = malloc(sizeof(int **));
    int **subsets_result = subsets(test_set, TEST_ARRAYSIZE, &return_size, return_cols);

    printf("======= print out =======\n");
    for(int i=0;i<return_size;i++) {
        for(int j=0;j<*(*return_cols+i);j++) {
            printf("%d, ", subsets_result[i][j]);
        }
        printf("\n");
    }

}

