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

// int test_set[] = {0};
// int test_set[] = {1, 2, 2};
// int test_set[] = {1, 2, 3, 4};
// int test_set[] = {1, 4, 4, 4, 4};
// int test_set[] = {4, 1, 0};
int test_set[] = {1,9,8,3,-1,0};
#define TEST_ARRAYSIZE (sizeof(test_set) / sizeof(int))



#define MODULE          1000007L
#define MAGIC_NUM       31L
#define MAX_SET_SIZE    10
#define MAX_SUBSET_SIZE 1025  // 2^N

long mod(long n, long m) {
    return (n % m + m) % m;
}

int cmp(int *a, int *b) {
    return *a - *b;
}

long hash(int *nums, int length, long *order_map) {
    long val = 0;
    for(int i=0;i<length;i++) {
        val += (nums[i]+11) * order_map[i];
    }
    return mod(val, MODULE);
}

bool is_in_hash(long *hash_map, int hash_size, long target) {
    for(int i=0;i<hash_size;i++) {
        if(hash_map[i] == target) return true;
    }
    return false;
}

void backtracking(int *nums, int **subsets, int *return_cols, int num_size, int *subset, int i_s, int index, long *hash_map, int *i_hash, long *order_map) {

    long subset_hash = hash(subset, i_s, order_map);

    printf("hash: %10ld, ", subset_hash);
    for(int i=0;i<i_s;i++) {
        printf("%d, ", subset[i]);
    }
    printf("\n");
    if(!is_in_hash(hash_map, (*i_hash)+1, subset_hash)) {
        *(subsets+(*i_hash)) = malloc(num_size*sizeof(int));
        memset(*(subsets+(*i_hash)), 0, num_size*sizeof(int));
        memcpy(*(subsets+(*i_hash)), subset, i_s*sizeof(int));
        *(return_cols+*i_hash) = i_s;
        hash_map[(*i_hash)++] = subset_hash;
    }
    else {
        printf("=====\n");
    }

    for(int i=index;i<num_size;i++) {
        subset[i_s++] = nums[i];
        backtracking(nums, subsets, return_cols, num_size, subset, i_s, i+1, hash_map, i_hash, order_map);
        i_s--;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int **subsets = malloc(MAX_SUBSET_SIZE*sizeof(int));
    memset(subsets, 0, MAX_SUBSET_SIZE*sizeof(int));

    int *retcolsizes = malloc(MAX_SUBSET_SIZE * sizeof(int));
    memset(retcolsizes, 0, MAX_SUBSET_SIZE * sizeof(int));
    *returnColumnSizes = retcolsizes;

    long *order_map = malloc(numsSize*sizeof(long));
    long *hash_map = malloc(100*sizeof(long));
    memset(hash_map, -1, 100*sizeof(long));
    order_map[0] = MAGIC_NUM;
    for(int i=1;i<numsSize;i++) {
        order_map[i] = order_map[i-1]*MAGIC_NUM;
    }


    // for loop find the all possible subset
    int *temp = malloc(sizeof(int)*numsSize);
    memset(temp, 0, sizeof(int)*numsSize);
    int i_hash = 0;
    backtracking(nums, subsets, retcolsizes, numsSize, temp, 0, 0, hash_map, &i_hash, order_map);

    *returnSize = i_hash;

    free(order_map);
    free(hash_map);
    return subsets;
}


int main(int argc, char *argv[]) {
    int return_size;
    
    int **return_cols = malloc(sizeof(int **));
    int **subsets = subsetsWithDup(test_set, TEST_ARRAYSIZE, &return_size, return_cols);

    printf("======= print out =======\n");
    for(int i=0;i<return_size;i++) {
        for(int j=0;j<*(*return_cols+i);j++) {
            printf("%d, ", subsets[i][j]);
        }
        printf("\n");
    }

}

