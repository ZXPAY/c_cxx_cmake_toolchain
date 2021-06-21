#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given an array nums of non-negative integers, return an array consisting of all the even elements of nums, 
followed by all the odd elements of nums.
You may return any answer array that satisfies this condition.
*/


int test_array[] = {3, 1, 2, 4};

int *sortArrayByParity(int *nums, int numsSize, int *returnSize){
    int *sort_par_arr = (int *)malloc(numsSize * sizeof(int));
    int odd_cnt = numsSize-1;
    int even_cnt = 0;
    *returnSize = 0;
    for(int i=0;i<numsSize;i++) {
        if(nums[i] & 0x1) {    // odd
            sort_par_arr[odd_cnt--] = nums[i];
        }
        else {                 // even
            sort_par_arr[even_cnt++] = nums[i];
        }
        (*returnSize)++;
    }
    return sort_par_arr;
}

int main(void) {
    printf("start \n");

    int returnSize;
    int *sor_par_arr = sortArrayByParity(test_array, sizeof(test_array)/sizeof(int), &returnSize);
    printf("return size: %d\n", returnSize);
    printf("sorting array by parity: \n");
    for(int i=0;i<returnSize;i++) {
        printf("%d, ", sor_par_arr[i]);
    }
    printf("\n");

    free(sor_par_arr);
    return 0;
}

