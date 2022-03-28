#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.
*/

int test_array[] = {4,5,6,7,0,1,2};
#define TARGET 0
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

int search(int *nums, int numsSize, int target) {
    int i_left = 0;
    int i_right = numsSize-1;
    
    // Array: Big small
    while(i_left <= i_right) {
        int i_mid = i_left + (i_right - i_left) / 2;

        if(target == nums[i_mid]) {
            // Got it !
            return i_mid;
        }
        else if(nums[i_left] < nums[i_mid]) {
            if(nums[i_left] <= target && target <= nums[i_mid]) {
                i_right = i_mid - 1;
            }
            else {
                i_left = i_mid + 1;
            }
        }
        else if(nums[i_right] > nums[i_mid]) {
            if(nums[i_mid] <= target && target <= nums[i_right]) {
                i_left = i_mid + 1;
            }
            else {
                i_right = i_mid - 1;
            }
        }
    }

    
    return -1;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", search(test_array, ARRAY_SIZE, TARGET));

}

