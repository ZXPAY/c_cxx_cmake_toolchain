#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_arr1[] = {1, 3, 10, 20};
int test_arr2[] = {2, 5, 6, 11};

int test_arr3[] = {1, 3};
int test_arr4[] = {2};

int test_arr5[] = {1, 2};
int test_arr6[] = {3, 4};

#define ARRAY_SIZE_OF(ARR)   (sizeof(ARR) / sizeof(int))

void median_help(int *nums1, int i1_l, int i1_r, int *nums2, int i2_l, int i2_r, int *count) {

    int i1_mid;
    int i2_mid;

    /* calculate mid index */
    if(i1_l <= i1_r) {
        i1_mid = (i1_l + i1_r) / 2;
        *count -= (i1_r - i1_mid) + 1;
    }
    else {
        i1_mid = -1;
    }
    if(i2_l <= i2_r) {
        i2_mid = (i2_l + i2_r) / 2;
        *count -= (i2_r - i2_mid) + 1;
    }
    else {
        i2_mid = -1;
    }

    printf("%d,%d, count: %d\n", i1_mid, i2_mid, *count);

    /* Main logic */
    if(*count == 0) {
        /* Got median value */
        printf("OK\n");
        return;
    }
    // else if(*count < 0) {
    //     assert(0);
    // }
    else if(*count > 0) {
        if(i1_mid != -1 &&  i2_mid != -1) {
            if(nums1[i1_mid] < nums2[i2_mid]) {
                /* 1 Go right */
                /* 2 Go left */
                median_help(nums1, i1_mid+1, i1_r, nums2, i2_l, i2_mid, count);
            }
            else {
                /* 1 Go left */
                /* 2 Go right */
                median_help(nums1, i1_l, i1_mid, nums2, i2_mid+1, i2_r, count);
            }
        }
        else if(i1_mid != -1) {
            if(*count < i1_mid) {
                /* 1 Go left */
                median_help(nums1, i1_l, i1_mid, nums2, i2_l, i2_r, count);
            }
            else {
                /* 1 Go right */
                median_help(nums1, i1_mid+1, i1_r, nums2, i2_l, i2_r, count);
            }
        }
        else if(i2_mid != -1) {
            if(*count < i2_mid) {
                /* 2 Go left */
                median_help(nums1, i1_l, i1_r, nums2, i2_l, i2_mid, count);
            }
            else {
                /* 2 Go right */
                median_help(nums1, i1_l, i1_r, nums2, i2_mid+1, i2_r, count);
            }
        }
        else {
            assert(0);
        }
    }


}


double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    int median_index = (nums1Size + nums2Size);

    median_help(nums1, 0, nums1Size-1, nums2, 0, nums2Size-1, &median_index);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result(5.5): %.2f\n", findMedianSortedArrays(test_arr1, ARRAY_SIZE_OF(test_arr1), test_arr2, ARRAY_SIZE_OF(test_arr2)));
    // printf("result(2.0): %.2f\n", findMedianSortedArrays(test_arr3, ARRAY_SIZE_OF(test_arr3), test_arr4, ARRAY_SIZE_OF(test_arr4)));
    // printf("result(2.5): %.2f\n", findMedianSortedArrays(test_arr5, ARRAY_SIZE_OF(test_arr5), test_arr6, ARRAY_SIZE_OF(test_arr6)));


}

