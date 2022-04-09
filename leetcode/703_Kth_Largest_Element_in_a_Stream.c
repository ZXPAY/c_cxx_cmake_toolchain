#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {
//     4, 5, 8, 2
// };
// #define K 3

int test_array[] = {
    0
};
#define K 2

#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_i_smaller(int *arr, int length, int index) {
    int i_final = -1;

    int i_left = index * 2 + 1;
    int i_right = index * 2;

    if(i_left <= length && i_right <= length) {
        if(arr[i_left] < arr[i_right]) {
            i_final = i_left;
        }
        else if(arr[i_left] >= arr[i_right]) {
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

    int i_smaller = get_i_smaller(arr, length, index);

    if(i_smaller == -1) return;
    else if(arr[index] > arr[i_smaller]) {
        // printf("swap %d, %d\n", index, i_smaller);
        swap(&arr[index], &arr[i_smaller]);
        shift_down(arr, length, i_smaller);
    }
}

/* BigO = log(n) */
void shift_up(int *arr, int index) {
    int i_parrent = index / 2;

    if(i_parrent <= 0) return;

    if(arr[index] < arr[i_parrent]) {
        // if smaller swap
        swap(&arr[index], &arr[i_parrent]);
        // shift up again
        shift_up(arr, i_parrent);
    }
}

typedef struct {
    int *arr;
    int k;
    int count;
} KthLargest;

KthLargest* kthLargestCreate(int k, int *nums, int numsSize);
int kthLargestAdd(KthLargest* obj, int val);
void kthLargestFree(KthLargest* obj);


KthLargest* kthLargestCreate(int k, int *nums, int numsSize) {
    KthLargest *kth = malloc(sizeof(KthLargest));
    kth->arr = malloc((k+1)*sizeof(int));
    memset(kth->arr, 0, (k+1)*sizeof(int));
    kth->k = k;

    kth->count = 0;

    for(int i=0;i<numsSize;i++) {
        kthLargestAdd(kth, nums[i]);
    }

    return kth;
}

int kthLargestAdd(KthLargest* obj, int val) {
    // Not full
    if(obj->count < obj->k) {
        obj->arr[obj->count+1] = val;
        shift_up(obj->arr, obj->count+1);
        obj->count++;
    }
    else if(val > obj->arr[1]) { // full and larger than root
        obj->arr[1] = val;
        shift_down(obj->arr, obj->count, 1);
    }
    for(int i=1;i<obj->count+1;i++) {
        printf("%d, ", obj->arr[i]);
    }
    printf("\n");
    return obj->arr[1];
}

void kthLargestFree(KthLargest* obj) {
    free(obj->arr);
    free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    KthLargest *kth = kthLargestCreate(K, test_array, ARRAY_SIZE);
    int temp;
    temp = kthLargestAdd(kth, -1);
    printf("=> %d\n", temp);
    temp = kthLargestAdd(kth, 1);
    printf("=> %d\n", temp);
    temp = kthLargestAdd(kth, -2);
    printf("=> %d\n", temp);
    temp = kthLargestAdd(kth, -4);
    printf("=> %d\n", temp);
    temp = kthLargestAdd(kth, 3);
    printf("=> %d\n", temp);

    for(int i=1;i<kth->count+1;i++) {
        printf("%d, ", kth->arr[i]);
    }
    printf("\n");


    kthLargestFree(kth);
}

