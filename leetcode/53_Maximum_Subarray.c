#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_array[] = {-2,1,-3,4,-1,2,1,-5,4};
#define ARRAY_SIZE sizeof(test_array) / sizeof(int)

int maxSubArray(int* nums, int numsSize) {
    if(numsSize == 1) return nums[0];
    
    int best_sum = nums[0];
    int current_sum = nums[0];
    for(int i=1;i<numsSize;i++) {
        if(current_sum > 0) current_sum += nums[i];
        else current_sum = nums[i];
        if(current_sum > best_sum) best_sum = current_sum;
    }

    return best_sum;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%d\n", maxSubArray(test_array, ARRAY_SIZE));

}

