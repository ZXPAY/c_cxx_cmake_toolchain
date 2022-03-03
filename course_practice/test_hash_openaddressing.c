#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


#define VALUE_NOTUSE      (-1)
#define VALUE_TOMBSTONE   INT_MIN

int test_array[] = {78,6,80,73,10,88};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

int *build_mod_hash(int *arr, int hash_size) {
    int *map = (int *)malloc(sizeof(int)*hash_size);
    memset(map, VALUE_NOTUSE, sizeof(int)*hash_size);


    // Build hash map
    for(int i=0;i<ARRAY_SIZE;i++) {
        int hash_index = arr[i] % 10;
        int count = 0;
        while(count++ < hash_size) {
            if(map[hash_index] == VALUE_NOTUSE) {
                map[hash_index] = arr[i];
                break;
            }
            else {
                hash_index++;
                if(hash_index == hash_size) hash_index = 0;
            }
        }
    }

    return map;
}

bool search(int *map, int target, int hash_size) {
    int hash_index = target % 10;
    int count = 0;
    while(count++ < hash_size) {
        if(map[hash_index] == target) return true;
        if(map[hash_index] == VALUE_NOTUSE) return false;

        hash_index++;
        if(hash_index == hash_size) hash_index = 0;
    }

    return false;
}


int main() {
    int hash_size = 10;
    int *map = build_mod_hash(test_array, hash_size);

    for(int i=0;i<hash_size;i++) {
        printf("[%d]: %d\n", i, map[i]);
    }

    for(int i=0;i<ARRAY_SIZE;i++) {
        // printf("=> %d\n", map[i]);
        if(search(map, test_array[i], hash_size)) {
            printf("Found: %d\n", test_array[i]);
        }
        else {
            printf("Not found\n");
        }
    }


    return 0;
}
