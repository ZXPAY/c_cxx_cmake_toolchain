#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_num[] = {1,2,3,4};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *runningSum(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize;
    for(int i=1;i<numsSize;i++) {
        nums[i] += nums[i-1];
    }

    return nums;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_sz = 0;
    int *result = runningSum(test_num, sizeof(test_num)/sizeof(int), &return_sz);
    printf("result: {");
    for(int i=0;i<return_sz;i++) {
        printf("%d,", result[i]);
    }
    printf("}\n");


}

