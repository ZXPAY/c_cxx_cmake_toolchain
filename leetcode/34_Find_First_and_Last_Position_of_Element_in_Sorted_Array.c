#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.
*/


// int test_array[] = {5, 7, 7, 8, 8, 10};
int test_array[] = {1, 2, 2};
#define ARRAY_SIZE  (sizeof(test_array) / (sizeof(int)))
#define TARGET      2

int *return_negative_one(void) {
    int *temp = (int *)malloc(sizeof(int)*2);
    memset(temp, -1, sizeof(int)*2);

    return temp;
}


int *search_help(int *nums, int target, int i_start, int i_end) {
    int *result = (int *)malloc(sizeof(int)*2);
    memset(result, -1, sizeof(int)*2);

    int i_mid = (i_start + i_end) / 2;

    if(nums[i_mid] == target) {
        // printf("find %d, %d, %d\n", i_start, i_mid, i_end);

        result[0] = i_mid;
        result[1] = i_mid;
        
        // Go left
        if(i_start < i_mid) {
            int *temp = search_help(nums, target, i_start, i_mid-1);
            if(temp[0] != -1) {
                result[0] = temp[0];
            }
            free(temp);
        }
        // Go right
        if(i_end > i_mid) {
            int *temp = search_help(nums, target, i_mid+1, i_end);
            if(temp[1] != -1) {
                result[1] = temp[1];
            }
            free(temp);
        }
    }
    else if(nums[i_mid] > target) {
        if(i_start < i_mid) {
            int *temp = search_help(nums, target, i_start, i_mid-1);
            if(temp[0] != -1 && temp[1] != -1) memcpy(result, temp, sizeof(int)*2);
            free(temp);
        }
    }
    else if(nums[i_mid] < target) {
        if(i_mid < i_end) {
            int *temp = search_help(nums, target, i_mid+1, i_end);
            if(temp[0] != -1 && temp[1] != -1) memcpy(result, temp, sizeof(int)*2);
            free(temp);
        }
    }

    // printf("%d, %d, %d, {%d, %d}\n", i_start, i_mid, i_end, result[0], result[1]);

    return result;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
    if(nums == NULL || numsSize <= 0) return return_negative_one();
    int *result;

    result = search_help(nums, target, 0, numsSize-1);

    *returnSize = 2;

    return result; 
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int returnsz = 0;

    int *result = searchRange(test_array, ARRAY_SIZE, TARGET, &returnsz);

    for(int i=0;i<returnsz;i++) {
        printf("%d, ", result[i]);
    }
    printf("\n");


    printf("end\n");

}

