#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {1,0,0,0,1,0,0,1};
// int test_array[] = {1,0,1};
// int test_array[] = {0,1,0,1};
int test_array[] = {0,1, 0,0,1,0,0,1};
#define K           2
#define ARRAY_SIZE sizeof(test_array) / sizeof(int)


/*
Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.
*/

bool kLengthApart(int *nums, int numsSize, int k) {
    int count = 0;
    if(nums[0] == 0) {
        count = k;
    }
    for(int i=1;i<numsSize;i++) {
        if(nums[i] == 1) {
            if(count < k) return false;
            count = 0;
        }
        else {
            count++;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("%d\n", kLengthApart(test_array, ARRAY_SIZE, K));

}

