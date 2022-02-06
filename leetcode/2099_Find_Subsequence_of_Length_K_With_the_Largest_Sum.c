#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
*/

int test1[] = {2, 1, 3, 3};
int test1_k = 2;
int test1_ans[] = {3, 3};

int test2[] = {-1, -2, 3, 4};
int test2_k = 3;
int test2_ans[] = {-1, 3, 4};

int test3[] = {3, 4, 3, 3};
int test3_k = 2;
int test3_ans[] = {3, 4};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize) {
    *returnSize = k;

    int *sub_seq = (int *)malloc(sizeof(int)*k);
    int minimal_val;
    int minimal_index = 0;

    for(int i=0;i<numsSize;i++) {
        // printf("%d\n", nums[i]);

        if(i < k) {
            sub_seq[i] = nums[i];

            if(0 == i) {
                minimal_val = nums[0];
                minimal_index = 0;
            }

            if(nums[i] < minimal_val) {
                minimal_val = nums[i];
                minimal_index = i;
            }

        }

        else {
            for(int j=0;j<k;j++) {
                if(nums[i] > sub_seq[j]) {
                    sub_seq[minimal_index] = nums[i];
                    break;
                }
            }
            int temp_index = 0;
            int temp_value = sub_seq[0];
            for(int j=1;j<k;j++) {
                if(sub_seq[j] < temp_value) {
                    temp_index = j;
                    temp_value = sub_seq[j];
                }
            }
            minimal_index = temp_index;
            minimal_val = temp_value;
        }
    }

    // bubble sorting
    for(int i=0;i<k;i++) {
        for(int j=i+1;j<k;j++) {
            if(sub_seq[j] < sub_seq[i]) {
                swap(&sub_seq[j], &sub_seq[i]);
            }
        }
    }    

    return sub_seq;
}



int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_size;

    int *test_data = test2;
    int test_size = sizeof(test2) / sizeof(int);
    int test_k = test2_k;

    int *result = maxSubsequence(test_data, test_size, test_k, &return_size);

    for(int i=0;i<return_size;i++) {
        printf("=> %d\n", result[i]);
    }

}

