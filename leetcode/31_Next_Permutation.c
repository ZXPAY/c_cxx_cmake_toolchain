#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {1, 2, 3};
#define ARRAY_SIZE   (sizeof(test_array) / sizeof(int))

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_array(int *nums, int i_left, int i_right) {
    while(i_left < i_right) {
        swap(&nums[i_left], &nums[i_right]);
        i_left++;
        i_right--;
    }
}

void nextPermutation(int *nums, int numsSize) {
    if(numsSize < 2) {
        return;
    }
    else if(numsSize < 3) {
        swap(&nums[0], &nums[1]);
        return;
    }
    
    /* Step 1: find the first descend value from numsSize-1 to zero */
    int i = numsSize - 2;
    while(i >=0 && nums[i]>=nums[i+1]) {
        i--;
    }
    // printf("= %d\n", i);

    /* Step 2: Swap the value greater the nums[i] from i to numsSize-1 */
    if(i >= 0) {
        int j = numsSize - 1;
        while(nums[i]>=nums[j]) {
            j--;
        }
        swap(&nums[i], &nums[j]);
        // printf("= %d\n", j);
    }

    /* Step 3: reverse the nums array */
    reverse_array(nums, i+1, numsSize-1);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("======= Before =======\n");
    for(int i=0;i<ARRAY_SIZE;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    nextPermutation(test_array, ARRAY_SIZE);
    
    printf("======= After =======\n");
    for(int i=0;i<ARRAY_SIZE;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");


}

