#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int test_array[] = {
    66, 78, 27, 35, 6, 2, 44, 58, 29, 76, 0, 0, 0, 0
};
int i_end = 9;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_i_bigger(int *arr, int length, int index) {
    int i_final = -1;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    if(i_left <= length && i_right <= length) {
        if(arr[i_left] >= arr[i_right]) {
            i_final = i_left;
        }
        else if(arr[i_left] < arr[i_right]) {
            i_final = i_right;
        }
    }
    else if(i_left <= length) {
        i_final = i_left;
    }
    else if(i_right <= length) {
        i_final = i_right;
    }


    return i_final;
}

/* BigO = log(n) */
void shift_down(int *arr, int length, int index) {
    if(index > i_end) return;

    int i_bigger = get_i_bigger(arr, length, index);

    if(i_bigger == -1) return;
    else if(arr[index] < arr[i_bigger]) {
        swap(&arr[index], &arr[i_bigger]);
        shift_down(arr, length, i_bigger);
    }
}

/* BigO = log(n) */
void shift_up(int *arr, int index) {
    if(index <= 0) return;

    int i_parrent = (index + 1) / 2 - 1;

    if(arr[index] > arr[i_parrent]) {
        // if bigger swap
        swap(&arr[index], &arr[i_parrent]);
        // shift up again
        shift_up(arr, i_parrent);
    }
}

/* BigO = n */
void build_heaptree(int *arr, int length) {
    for(int i=length-1;i>=0;i--) {
        shift_down(arr, length, i);
    }
}

void remove_from_top(int *arr, int length) {
    if(length <= 0) return;

    /* step01: swap the node with last node */
    swap(&arr[0], &arr[i_end]);

    /* step02: array size -1 */
    i_end--;

    /* step03: shift down the current top node */
    shift_down(arr, i_end, 0);
}

void add_to_heap_tree(int *arr, int val) {
    i_end++;
    arr[i_end] = val;

    shift_up(arr, i_end);
}


int main() {
    printf("start\n");

    build_heaptree(test_array, i_end+1);

    for(int i=0;i<i_end+1;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("remove from top\n");
    remove_from_top(test_array, i_end);
    for(int i=0;i<i_end+2;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("add value 100 and 120\n");
    add_to_heap_tree(test_array, 100);
    add_to_heap_tree(test_array, 120);
    for(int i=0;i<i_end+1;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    return 0;
}

