#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
Given an integer array nums, return the number of arithmetic subarrays of nums.

A subarray is a contiguous subsequence of the array.
 
*/

// arithmetic subsequece num   counter
// 3           ->                 1
// 4           ->                 3
// 5           ->                 6
// 6           ->                 10
// 7           ->                 15

// int test_num[] = {1, 2, 3, 4};  // answer is 3
// int test_num[] = {1, 2, 3, 4, 5, 6, 7};  // answer is 10
// int test_num[] = {-1, -2, -3, 4};  // answer is 1
int test_num[] = {1, 2, 3, 8, 9, 10, 20};  // answer is 2
// int test_num[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  // answer is 128

int numberOfArithmeticSlices(int *nums, int numsSize) {
    if(numsSize < 3) return 0;
    int result = 0;

    /* Start at 3 to end numsSize, for loop, performance bad */
    // int cnt = 0;
    // int temp_value = 0;
    // for(int k=3;k<=numsSize;k++) {
    //     for(int i=0;i<numsSize-k+1;i++) {
    //         for(int j=i+1;j<i+k;j++) {
    //             if(j == i+1) {
    //                 cnt = 0;
    //                 temp_value = nums[j] - nums[j-1];
    //             }
    //             if(nums[j] - nums[j-1] != temp_value) {
    //                 cnt = 0;
    //                 continue;
    //             }
    //             else {
    //                 cnt++;
    //             }
    //             if(cnt == k-1) {   // start from zero
    //                 // printf("found: %d\n", k);
    //                 cnt = 0;
    //                 result++;
    //             }
    //         }
    //         // printf("====\n");
    //     }
    // }

    /* Optimization */
    int arti_index = 0, inc_count = 1;
    for(int i=1;i<numsSize-1;i++) {
        if((nums[i+1] - nums[i]) == (nums[i] - nums[i-1])) {
            arti_index++;
        }
        else {
            if(arti_index > 0) result += inc_count;
            arti_index = 0;
            inc_count = 1;
        }
        if(arti_index > 1) {
            inc_count += arti_index;
        }
        // printf("arti: %d, %d, %d\n", arti_index, inc_count, result);
    }
    if(arti_index > 0) result += inc_count;

    return result;
}

int main() {
    printf("start\n");

    printf("numberOfArithmeticSlices: %d\n", numberOfArithmeticSlices(test_num, sizeof(test_num)/sizeof(int)));
}

