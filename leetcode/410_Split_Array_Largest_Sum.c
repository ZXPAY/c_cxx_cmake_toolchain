#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {7, 2, 5, 10, 8};  // m=2, ans=18
// int test_array[] = {1, 4, 4};   // m=3, ans=4
// int test_array[] = {2, 3, 1, 2, 4, 3};   // m=5, ans=4
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))
#define M 2

/*
Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.
*/


int get_howmany_subarray(int *nums, int numsSize, int max_val, int *max_sum) {
    int temp = 0;
    int count = 0;
    for(int i=0;i<numsSize;i++) {
        if(temp + nums[i] > max_val) {
            temp = nums[i];
            count++;
        }
        else {
            temp += nums[i];
        }
        if(*max_sum < temp) *max_sum = temp;
    }

    return count + 1;
}

int search_help(int *nums, int numsSize, int sum_l, int sum_h, int m) {
    int mid_sum = (sum_l + sum_h) / 2;
    int result = -1;

    int max_sum_in_array = 0;
    int split_n = get_howmany_subarray(nums, numsSize, mid_sum, &max_sum_in_array);
    printf("%3d, %2d, %2d\n", mid_sum, split_n, max_sum_in_array);

    if(split_n <= m) {
        result = max_sum_in_array;
        // Go left
        if(sum_l < mid_sum) {
            int temp = search_help(nums, numsSize, sum_l, mid_sum-1, m);
            if(temp != -1) result = temp;
        }
    }
    else if(split_n > m) {
        // Go right
        if(sum_h > mid_sum) {
            int temp = search_help(nums, numsSize, mid_sum+1, sum_h, m);
            if(temp != -1) result = temp;
        }
    }


    return result;    
}

int splitArray(int *nums, int numsSize, int m) {
    int sum_val = 0;
    int min_val = nums[0];
    int max_val = nums[0];
    for(int i=0;i<numsSize;i++) {
        sum_val += nums[i];
        if(min_val > nums[i]) min_val = nums[i];
        if(max_val < nums[i]) max_val = nums[i];
    }

    if(numsSize == m) {
        return max_val;
    }
    return search_help(nums, numsSize, min_val, sum_val, m);
}


int main(int argc, char *argv[]) {

    printf("result: %d\n", splitArray(test_array, ARRAY_SIZE, M));

}

