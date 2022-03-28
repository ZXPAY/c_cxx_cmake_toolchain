#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.
*/

// int test_array[] = {4,5,6,7,0,1,2};
int test_array[] = {1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1};
#define TARGET 13

#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

bool search(int *nums, int numsSize, int target) {
    int i_left = 0;
    int i_right = numsSize-1;
    
    while(i_left <= i_right) {
        int i_mid = i_left + (i_right - i_left) / 2;
        // printf("= %d, %d, %d\n", i_left, i_mid, i_right);

        if(target == nums[i_mid]) {
            // Got it !
            return true;
        }
        else if(nums[i_left] < nums[i_mid]) {
            if(nums[i_left] <= target && target < nums[i_mid]) {
                i_right = i_mid - 1;
            }
            else {
                i_left = i_mid + 1;
            }
        }
        else if(nums[i_left] > nums[i_mid]) {
            if(nums[i_mid] < target && target < nums[i_left]) {
                i_left = i_mid + 1;
            }
            else {
                i_right = i_mid - 1;
            }
        }
        else {
            i_left++;
        }
    }

    
    return false;
}

bool search2(int *nums, int numsSize, int target) {
    for(int i=0;i<numsSize;i++) {
        if(nums[i] == target) return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", search(test_array, ARRAY_SIZE, TARGET));
    printf("result: %d\n", search2(test_array, ARRAY_SIZE, TARGET));

}

