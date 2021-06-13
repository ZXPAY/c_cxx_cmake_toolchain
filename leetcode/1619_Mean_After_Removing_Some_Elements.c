#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

/* @brief Given an integer array arr, return the mean of the remaining integers after 
*         removing the smallest 5% and the largest 5% of the elements.
*         Answers within 10-5 of the actual answer will be considered accepted.
*/

// Quick sort in math library
extern void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

int test_array[] = {
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3
};

// int test_array[] = {
//     6,2,7,5,1,2,0,3,10,2,5,0,5,5,0,8,7,6,8,0
// };

// int test_array[] = {
//     6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4
// };

void swap(int *a, int *b) {
    assert(a != NULL && b != NULL);
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sorting(int *arr, int arrSize) {
    int temp_min_index = 0;
    for(int i=0;i<arrSize;i++) {
        temp_min_index = i;
        for(int j=i;j<arrSize;j++) {
            if(arr[j] < arr[temp_min_index]) {
                temp_min_index = j;
            }
        }
        swap(&arr[i], &arr[temp_min_index]);
    }
}

static int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

double trimMean(int *arr, int arrSize){
    int temp_sum = 0;

    // sorting(arr, arrSize);
    qsort(arr, arrSize, sizeof(int), cmpfunc);

    int low_5 = (int)(round(arrSize*0.05));
    int hight_5 = (int)(round(arrSize*0.95));
    printf("%d, %d\n", low_5, hight_5);
    for(int i=low_5;i<hight_5;i++) {
        temp_sum += *(arr+i);
    }
    return (double)temp_sum / (double)(hight_5 - low_5);
}

int main() {
    printf("start\n");
    int arr_sz = sizeof(test_array) / sizeof(int);
    int low_5 = (int)(arr_sz*0.05);
    int hight_5 = (int)(arr_sz*0.95);
    printf("data size is %d, %d, %d\n", arr_sz, low_5, hight_5);
    for(int i=0;i<arr_sz;i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");
    printf("mean is %.5f\n", trimMean((int *)test_array, arr_sz));
}
