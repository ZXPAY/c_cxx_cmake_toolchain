#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
                22
        0              44
    X       11      33    55
           X  X    X  X  X  X

*/

int search_help(int *nums, int val, int i_left, int i_right) {
    if(i_right < i_left) return -1;
    int result = -1;
    int i_mid = (i_left + i_right) / 2;

    // printf("%d, %d, %d\n", i_left, i_mid, i_right);

    if(val == nums[i_mid]) {
        result = val;
        return result;
    }
    else if(val < nums[i_mid]) {
        // Go left
        int tmp_left = search_help(nums, val, i_left, i_mid-1);
        if(tmp_left != -1) {
            result = tmp_left;
        }
    }
    else if(val > nums[i_mid]) {
        // Go right
        int tmp_right = search_help(nums, val, i_mid+1, i_right);
        if(tmp_right != -1) {
            result = tmp_right;
        }
    }


    return result;
}

int search(int *nums, int val, int length) {

    int result = search_help(nums, val, 0, length-1);

    return result;
}

int test_array[] = {   // sorted array
    0, 11, 22, 33, 44, 55
};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

int main() {
    printf("start\n");

    int temp = search(test_array, 55, ARRAY_SIZE);

    if(temp != -1) {
        printf("find %d\n", temp);
    }
    else {
        printf("Not found !!!\n");
    }

    return 0;
}


