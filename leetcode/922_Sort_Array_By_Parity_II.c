#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given an array of integers nums, half of the integers in nums are odd, and the other half are even.

Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.

Return any answer array that satisfies this condition.
*/


int test_array[] = {4,2,5,7};

int *sortArrayByParityII(int *nums, int numsSize, int *returnSize){
    int *sort_par_arr = (int *)malloc(numsSize * sizeof(int));
    int odd_cnt = 1;
    int even_cnt = 0;
    *returnSize = 0;
    for(int i=0;i<numsSize;i++) {
        if(nums[i] & 0x1) {    // odd
            sort_par_arr[odd_cnt] = nums[i];
            odd_cnt += 2;
        }
        else {                 // even
            sort_par_arr[even_cnt] = nums[i];
            even_cnt += 2;
        }
        (*returnSize)++;
    }
    return sort_par_arr;
}

int main(void) {
    printf("start \n");

    int returnSize;
    int *sor_par_arr = sortArrayByParityII(test_array, sizeof(test_array)/sizeof(int), &returnSize);
    printf("return size: %d\n", returnSize);
    printf("sorting array by parityII: \n");
    for(int i=0;i<returnSize;i++) {
        printf("%d, ", sor_par_arr[i]);
    }
    printf("\n");

    free(sor_par_arr);
    return 0;
}
