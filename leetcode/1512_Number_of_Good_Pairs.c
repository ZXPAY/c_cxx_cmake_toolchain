#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Given an array of integers nums.

A pair (i,j) is called good if nums[i] == nums[j] and i < j.

Return the number of good pairs.

*/


// int nums[] = {1,2,3,1,1,3};   // answer is 4
int nums[] = {1,1,1,1};       // answer is 6

int numIdenticalPairs(int *nums, int numsSize){
    int result = 0;
    for(int i=0;i<numsSize;i++) {
        for(int j=i+1;j<numsSize;j++) {   // i < j
            if(nums[i] == nums[j]) {
                result++;
            }
        }
    }
    return result;
}

int main() {
    printf("start\n");

    printf("numIdenticalPairs: %d\n", numIdenticalPairs(nums, sizeof(nums)/sizeof(int)));
}
