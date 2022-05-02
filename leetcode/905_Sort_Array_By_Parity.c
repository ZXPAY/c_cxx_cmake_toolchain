#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {3, 1, 2, 4};
#define ARRAY_SIZE   (sizeof(test_array) / sizeof(int))

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortArrayByParity(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize;
    int i_l = 0;
    int i_r = numsSize-1;
    
    while(i_r > i_l) {
        // four case
        int nl = nums[i_l]&1;
        int nr = nums[i_r]&1;
        if(nl && nr) {
            i_r--;
        }
        else if(nl && !nr) {
            swap(&nums[i_l], &nums[i_r]);
            i_r--;
            i_l++;
        }
        else if(!nl && nr) {
            i_r--;
            i_l++;
        }
        else if(!nl && !nr) {
            i_l++;
        }
    }
    
    return nums;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("{");
    for(int i=0;i<ARRAY_SIZE;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("}\n");


    int ret_sz = 0;
    int *result = sortArrayByParity(test_array, ARRAY_SIZE, &ret_sz);

    printf("{");
    for(int i=0;i<ret_sz;i++) {
        printf("%d, ", result[i]);
    }
    printf("}\n");


}

