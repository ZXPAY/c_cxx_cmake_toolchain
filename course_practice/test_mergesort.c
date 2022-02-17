#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*
* Branch and sort, BST post-order
*/

int test_array[] = {20, 10, 50, 30, 70, 60, 40};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

void sort(int *nums, int i_low, int i_mid, int i_high, int length) {
    int *tmp_nums = (int *)malloc(sizeof(int)*length);
    int i_num_tmp = i_low;     // low   ~ high
    int i_left_arr = i_low;    // low   ~ mid
    int i_right_arr = i_mid + 1; // mid+1 ~ high
    
    while(true) {
        if(i_num_tmp > i_high) break;

        int left_num = -1;
        int right_num = -1;

        /* pick one number from left array */
        if(i_left_arr <= i_mid) {
            left_num = nums[i_left_arr];
        }
        if(i_right_arr <= i_high) {
            right_num = nums[i_right_arr];
        }

        /* compare and put into nums_tmp array */
        if(-1 != left_num && -1 != right_num) {
            if(left_num <= right_num) {
                tmp_nums[i_num_tmp] = left_num;
                i_left_arr++;
            }
            if(left_num > right_num) {
                tmp_nums[i_num_tmp] = right_num;
                i_right_arr++;
            }
        }
        else if(-1 != left_num && -1 == right_num) {
            tmp_nums[i_num_tmp] = left_num;
            i_left_arr++;
        }
        else if(-1 == left_num && -1 != right_num) {
            tmp_nums[i_num_tmp] = right_num;
            i_right_arr++;
        }
        else {
            assert(0);
        }

        i_num_tmp++;
    }

    /** copy back to original array **/
    int k = i_low;
    while (true) {
        if (k > i_high) break;
        nums[k] = tmp_nums[k];

        k++;
    }
}

void traverse_postorder(int *nums, int i_low, int i_high, int length) {
    /* Go back condition */
    if(i_low == i_high) return;  // one element means sorted already
    
    /* main logic */
    int i_mid = (i_low + i_high) / 2;

    /* data flow */
    traverse_postorder(nums, i_low, i_mid, length);
    traverse_postorder(nums, i_mid+1, i_high, length);

    sort(nums, i_low, i_mid, i_high, length);

}

void merge_sort(int *nums, int length) {
    traverse_postorder(nums, 0, ARRAY_SIZE-1, ARRAY_SIZE);
}

int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("start sorting\n");
    merge_sort(test_array, ARRAY_SIZE);
    

    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");
}

