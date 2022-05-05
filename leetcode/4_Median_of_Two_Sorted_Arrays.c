#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_arr1[] = {1,2,4};
int test_arr2[] = {3,5,7};

int test_arr3[] = {1, 3};
int test_arr4[] = {2};

int test_arr5[] = {1, 2};
int test_arr6[] = {3, 4};

#define ARRAY_SIZE_OF(ARR)   (sizeof(ARR) / sizeof(int))

int search_index(int *nums, int i_left, int i_right, int target) {
    if(i_left > i_right) return i_left-1;
    if(i_left == 0 && i_right == 0) return 0;

    int i_mid = (i_left + i_right) / 2;

    if(nums[i_mid] == target) {
        return i_mid;
    }
    else if(i_mid+1 <= i_right && nums[i_mid] < target && nums[i_mid+1] > target) {
        return i_mid;
    }
    else if(i_mid-1 >= i_left && nums[i_mid] > target && nums[i_mid-1] < target) {
        return i_mid-1;
    }
    else if(nums[i_mid] < target) {
        return search_index(nums, i_mid+1, i_right, target);
    }
    else if(nums[i_mid] > target) {
        return search_index(nums, i_left, i_mid, target);
    }

    return -1;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    int median_index = (nums1Size + nums2Size)/2;
    bool fg2 = (nums1Size&1)==(nums2Size&1)?true:false;

    int b0_in_a_index = search_index(nums1, 0, nums1Size-1, nums2[0]);
    int bend_in_a_index = search_index(nums1, 0, nums1Size, nums2[nums2Size-1]);

    if(b0_in_a_index == (nums1Size-1)) {
        if(fg2) {
            if(nums1Size == nums2Size) return (nums1[nums1Size-1]+nums2[0])/2.0;
            return (double) (nums2[median_index-nums1Size-1] + nums2[median_index-nums1Size])/2.0;
        }
        else {
            return nums2[median_index-nums1Size];
        }
    }
    else if(bend_in_a_index == 0) {
        if(fg2) {
            if(nums1Size == nums2Size) return (nums2[nums1Size-1]+nums1[0])/2.0;
            return (double) (nums1[median_index-nums2Size-1] + nums1[median_index-nums2Size])/2.0;
        }
        else {
            return nums1[median_index-nums2Size];
        }
    }
    else {
        int i_n1_l = 0;
        int i_n1_r = nums1Size-1;
        for(int i=0;i<nums2Size;i++) {
            int temp = search_index(nums1, i_n1_l, i_n1_r, nums2[i]);
            if(temp+i+1 == median_index) {
                printf("found\n");
            }
            else if(temp+i+1 < median_index) {}
            printf("array index: %d\n", temp+i+1);

        }

    }

    return 0.0;
}

double findMedianSortedArrays_sol2(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if(nums1Size == 0) {
        if(nums2Size & 1) {
            return (double)nums2[nums2Size/2];
        }
        else {
            return (double) (nums2[nums2Size/2-1]+nums2[nums2Size/2])/2.0;
        }
    }
    else if(nums2Size == 0) {
        if(nums1Size & 1) {
            return (double)nums1[nums1Size/2];
        }
        else {
            return (double) (nums1[nums1Size/2-1]+nums1[nums1Size/2])/2.0;
        }
    }
    int i1 = 0;
    int i2 = 0;
    int i_m = (nums1Size + nums2Size)/2;
    int fg = (nums1Size&1)==(nums2Size&1)?1:0;
    if(fg) i_m--;
    double res = 0;
    while(i1<nums1Size || i2<nums2Size) {
        // printf("%d, %d\n", i1, i2);

        if(i2 < nums2Size && i1 < nums1Size && nums1[i1] < nums2[i2]) {
            if(i1+i2 == i_m || i1+i2 == i_m+1) {
                res += nums1[i1];

                if(fg == 1) {
                    fg = 3;
                }
                else {
                    break;
                }
            }
            i1++;
        }
        else if(i2>=nums2Size) {
            if(i1+i2 == i_m || i1+i2 == i_m+1) {
                res += nums1[i1];

                if(fg == 1) {
                    fg = 3;
                }
                else {
                    break;
                }
            }
            i1++;
        }
        else {
            if(i1+i2 == i_m || i1+i2 == i_m+1) {
                res += nums2[i2];

                if(fg == 1) {
                    fg = 3;
                }
                else {
                    break;
                }
            }
            i2++;
        }
    }

    if(fg == 3) return res/2.0;

    return res;
}



int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result(5.5): %.2f\n", findMedianSortedArrays(test_arr1, ARRAY_SIZE_OF(test_arr1), test_arr2, ARRAY_SIZE_OF(test_arr2)));
    // printf("result(2.0): %.2f\n", findMedianSortedArrays(test_arr3, ARRAY_SIZE_OF(test_arr3), test_arr4, ARRAY_SIZE_OF(test_arr4)));
    // printf("result(2.5): %.2f\n", findMedianSortedArrays(test_arr5, ARRAY_SIZE_OF(test_arr5), test_arr6, ARRAY_SIZE_OF(test_arr6)));


}

