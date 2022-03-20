#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {-1,0,3,5,9,12};
#define TARGET 9
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

/*
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.
*/

#define VALUE_NOT_USEED INT32_MIN
int search_help(int *nums, int target, int i_left, int i_right) {
    if(i_left > i_right) return 0;
    int result = VALUE_NOT_USEED;
    
    int i_mid = (i_left + i_right) / 2;

    if(nums[i_mid] == target) {
        // Find the target
        return i_mid;
    }
    else if(nums[i_mid] > target) {
        // Go left
        int temp = search_help(nums, target, i_left, i_mid-1);
        if(temp != VALUE_NOT_USEED) {
            result = temp;
        }
    }
    else if(nums[i_mid] < target) {
        // Go right
        int temp = search_help(nums, target, i_mid+1, i_right);
        if(temp != VALUE_NOT_USEED) {
            result = temp;
        }
    }

    return result;    
}

int search(int *nums, int numsSize, int target) {
    int res = search_help(nums, target, 0, numsSize-1);
    if(target != nums[res]) return -1;

    return res;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("%d\n", search(test_array, ARRAY_SIZE, TARGET));

}

