#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


// int test_array[] = {1,2,3,4};  // false
// int test_array[] = {3,1,4,2};  // true
// int test_array[] = {1,3,4,2};  // true
// int test_array[] = {3,5,0,3,4};  // true
// int test_array[] = {1,3,2};      // true
// int test_array[] = {1,0,1,-4,-3};      // false
int test_array[] = {1,4,0,-1,-2,-3,-1,-2}; // true

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(int))

bool find132pattern(int *nums, int numsSize) {
    if(numsSize < 3) return false;

    int i_buf = 0;
    int *stack_buf = malloc(numsSize*sizeof(int));
    int third_n = INT32_MIN;

    /* 1 3 2 => 2 3 1, numsSize-1 to 0 */
    for(int i=numsSize-1;i>=0;i--) {
        if(nums[i] < third_n) return true;
        while(i_buf > 0 && stack_buf[i_buf-1] < nums[i]) {
            /* Update local maximum */
            third_n = stack_buf[--i_buf];
        }
        stack_buf[i_buf++] = nums[i];
    }

    return false;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }



    printf("%d\n", find132pattern(test_array, ARR_SIZE(test_array)));


}

