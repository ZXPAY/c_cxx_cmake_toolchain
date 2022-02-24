#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


int test_array[] = {78,6,80,73,27,61,35,44,29,2};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

int *build_linear_hash(int *arr, int arr_size) {
    // Find the max value
    int temp = arr[0];
    for(int i=1;i<arr_size;i++) {
        if(arr[i] > temp) temp = arr[i];
    }

    int *map = (int *)malloc(sizeof(int) * temp);
    memset(map, -1, sizeof(int)*temp);

    // Build hash map
    for(int i=0;i<arr_size;i++) {
        map[arr[i]] = arr[i];
    }

    return map;
}

bool search(int *map, int target) {
    if(map[target] == target) return true;

    return false;
}

int main() {

    int *map = build_linear_hash(test_array, ARRAY_SIZE);

    for(int i=0;i<ARRAY_SIZE;i++) {
        if(search(map, test_array[i])) {
            printf("Found: %d\n", test_array[i]);
        }
        else {
            printf("Not found\n");
        }
    }


    return 0;
}
