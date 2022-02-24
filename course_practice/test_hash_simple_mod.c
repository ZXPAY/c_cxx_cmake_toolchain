#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


/* Not handle collision */

int test_array[] = {78,6,80,73,27,61,35,44,29,2};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

int *build_mod_hash(int *arr, int arr_size) {
    int *map = (int *)malloc(sizeof(int) * arr_size);
    memset(map, -1, sizeof(int)*arr_size);


    // Build hash map
    for(int i=0;i<arr_size;i++) {
        int hash_index = arr[i] % 10;
        map[hash_index] = arr[i];
    }

    return map;
}

bool search(int *map, int target) {
    if(map[target%10] == target) return true;

    return false;
}

int main() {

    int *map = build_mod_hash(test_array, ARRAY_SIZE);

    for(int i=0;i<ARRAY_SIZE;i++) {
        // printf("=> %d\n", map[i]);
        if(search(map, test_array[i])) {
            printf("Found: %d\n", test_array[i]);
        }
        else {
            printf("Not found\n");
        }
    }


    return 0;
}
