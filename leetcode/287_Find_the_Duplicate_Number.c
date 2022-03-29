#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {1,3,4,3,2};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

/*
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.
*/


int findDuplicate(int *nums, int numsSize) {
    bool *seen_number = malloc(numsSize*sizeof(bool));
    memset(seen_number, 0, numsSize*sizeof(bool));

    for(int i=0;i<numsSize;i++) {
        assert(nums[i] < numsSize);
        if(seen_number[nums[i]]) return nums[i];
    
        seen_number[nums[i]] = true;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", findDuplicate(test_array, ARRAY_SIZE));

}

