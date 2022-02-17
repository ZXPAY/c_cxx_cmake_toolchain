#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>


/*
* Sorting and branch, BST pre-order
*/

int test_array[] = {20, 10, 50, 30, 70, 60, 40};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int sort(int *nums, int pivot_i_guest, int i_start, int i_end) {
    int i_pivot_now = pivot_i_guest;

    swap(&nums[pivot_i_guest], &nums[i_end]);

    // update the pivot postion
    i_pivot_now = i_end;

    int i_left = i_start;
    int i_right = i_end - 1;

    while (true) {
        while(true) {
            if(i_left == i_right) break;
            if(nums[i_left] > nums[i_pivot_now]) break;
            i_left++;
        }
        while(true) {
            if(i_left == i_right) break;
            if(nums[i_right] < nums[i_pivot_now]) break;
            i_right--;
        }
        if(i_left == i_right) break;
        
        swap(&nums[i_left], &nums[i_right]);
    }

    int i_meeting_point = i_left;
    if (nums[i_meeting_point] >= nums[i_pivot_now]) {
        swap(&nums[i_pivot_now], &nums[i_meeting_point]);
        i_pivot_now = i_meeting_point;
    }

    return i_pivot_now;
}

// sort and branch
void traverse_preorder(int *nums, int i_left, int i_right) {
    /* Go back condition */
    if(i_left == i_right) return;  // one element means sorted already
    if(i_left > i_right) return;   // out of bond


    int i_pivot = (i_left + i_right) / 2;

    /* main logic */
    int i_pivot_final = sort(nums, i_pivot, i_left, i_right);


    /* data flow */
    traverse_preorder(nums, i_left, i_pivot_final-1);
    traverse_preorder(nums, i_pivot+1, i_right);
    
}

void quick_sort(int *nums, int length) {
    traverse_preorder(nums, 0, ARRAY_SIZE-1);
}

int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("start sorting\n");
    quick_sort(test_array, ARRAY_SIZE);
    

    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");
}
