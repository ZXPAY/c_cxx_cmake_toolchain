#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.

For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
Given an array nums, return the sum of all XOR totals for every subset of nums. 

Note: Subsets with the same elements should be counted multiple times.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.

*/

int test_num[] = {10,5,8,3,6,12,2,4,11,7,1,9};  // answer is 30720

void xor_subset_sum(int *nums, int *sum_xor, int *arr, int arr_index, int k, int numsSize) {
    if(k >= numsSize) {
        int temp_xor = 0;
        for(int i=0;i<arr_index;i++) {
            // printf("%d, %d\n", arr[i], nums[arr[i]]);
            if(0 == i) {
                temp_xor = nums[arr[i]];
                continue;
            }
            temp_xor ^= nums[arr[i]];
        }
        *sum_xor += temp_xor;
        // printf("============\n");
    }
    else {
        arr[arr_index++] = k;
        xor_subset_sum(nums, sum_xor, arr, arr_index, k+1, numsSize);

        arr[arr_index--] = 0;
        xor_subset_sum(nums, sum_xor, arr, arr_index, k+1, numsSize);
    }
}


int subsetXORSum(int *nums, int numsSize){
    // int *arr = (int *)malloc(numsSize * sizeof(int));
    assert(numsSize<=12);
    int arr[13];
    memset(arr, 0, numsSize*sizeof(int));
    int arr_index = 0;
    int sum_xor = 0;
    xor_subset_sum(nums, &sum_xor, arr, arr_index, 0, numsSize);
    return sum_xor;
}

int main() {
    printf("start\n");

    printf("subsetXORSum: %d\n", subsetXORSum(test_num, sizeof(test_num) / sizeof(int)));

}
