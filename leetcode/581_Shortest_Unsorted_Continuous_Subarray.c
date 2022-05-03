#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array1[] = {2,6,4,8,10,9,15,3}; // ans: 7
int test_array2[] = {2,3,3,2,4};         // ans: 3
int test_array3[] = {1,3,2,3,3};         // ans: 2
int test_array4[] = {1,2,3,3,3};         // ans: 0
int test_array5[] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5}; // ans: 13
int test_array6[] = {1,3,2,2,2}; // ans: 4
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(int))

typedef struct {
    int min_val;
    int max_val;
} neg_slope_extremum_t;

int findUnsortedSubarray(int *nums, int numsSize) {
    if(numsSize < 2) return 0;

    neg_slope_extremum_t slope_neg = {
        .min_val = INT32_MAX,
        .max_val = INT32_MIN,
    };

    /* collect the slope < 0, max and min val */
    for(int i=1;i<numsSize;i++) {
        if(nums[i] < nums[i-1]) {
            if(nums[i] < slope_neg.min_val) slope_neg.min_val = nums[i];
            if(nums[i-1] > slope_neg.max_val) slope_neg.max_val = nums[i-1];
        }
    }

    /* If there is no slope < 0, return 0 */
    if(slope_neg.max_val == INT32_MIN && slope_neg.min_val == INT32_MAX) return 0;

    /* Find the left and right index */
    int i_l = 0;
    int i_r = 0;
    for(int i=0;i<numsSize;i++) {
        if(nums[i] >= slope_neg.min_val) {
            i_l = i;
            break;
        }
    }
    for(int i=numsSize-1;i>=0;i--) {
        if(nums[i] <= slope_neg.max_val) {
            i_r = i;
            break;
        }
    }
    
    /* Handle duplicated value */
    while(true) {
        if(nums[i_r] == slope_neg.max_val) {
            i_r--;
        }
        else if(nums[i_l] == slope_neg.min_val) {
            i_l++;
        } 
        else {
            break;
        }
    }
    
    return i_r - i_l + 1;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result1[ 7]: %d\n", findUnsortedSubarray(test_array1, ARRAY_SIZE(test_array1)));
    printf("result2[ 3]: %d\n", findUnsortedSubarray(test_array2, ARRAY_SIZE(test_array2)));
    printf("result3[ 2]: %d\n", findUnsortedSubarray(test_array3, ARRAY_SIZE(test_array3)));
    printf("result4[ 0]: %d\n", findUnsortedSubarray(test_array4, ARRAY_SIZE(test_array4)));
    printf("result5[13]: %d\n", findUnsortedSubarray(test_array5, ARRAY_SIZE(test_array5)));
    printf("result6[ 4]: %d\n", findUnsortedSubarray(test_array6, ARRAY_SIZE(test_array6)));


}

