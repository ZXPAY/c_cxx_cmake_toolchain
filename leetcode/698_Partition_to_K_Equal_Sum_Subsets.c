#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


// int test_array[] = {4,3,2,3,5,2,1};  // k=4, true
// int test_array[] = {1,2,3,4};  // k=3, false
// int test_array[] = {1,1,1,1,9};  // k=2, false
// int test_array[] = {2,2,2,2,3,4,5};  // k=4, false
// int test_array[] = {4,4,4,6,1,2,2,9,4,6};  // k=3, true
int test_array[] = {6,5,9,6,3,5,1,10,4,1,4,3,9,9,3,3};  // k=9, true
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))
#define K  9

bool backtracking(int *nums, int numsSize, int index, int count, int target, bool *seen, int sum) {
    if(1 == count) return true;

    if(sum > target) return false;
    else if(sum == target) {
        return backtracking(nums, numsSize, 0, count-1, target, seen, 0);
    }

    for(int i=index;i<numsSize;i++) {
        if(!seen[i] && sum+nums[i]<=target) {
            seen[i] = true;
            if(backtracking(nums, numsSize, i+1, count, target, seen, sum+nums[i])) return true;
            seen[i] = false;
        }
    }

    return false;
}

int cmp(int *a, int *b) {
    return *b - *a;
}

bool canPartitionKSubsets(int *nums, int numsSize, int k) {
    bool *seen = malloc(numsSize*sizeof(bool));
    memset(seen, 0, numsSize*sizeof(bool));

    int temp_sum = 0;
    for(int i=0;i<numsSize;i++) temp_sum += nums[i];
    if(temp_sum % k) return false;

    printf("Target: %d\n", temp_sum / k);

    qsort(nums, numsSize, sizeof(int), cmp);
    return backtracking(nums, numsSize, 0, k, temp_sum/k, seen, 0);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", canPartitionKSubsets(test_array, ARRAY_SIZE, K));

}

