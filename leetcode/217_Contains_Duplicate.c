#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {1, 2, 3, 1};


#define VALUE_NOTUSE INT32_MIN

int mod(int n, int m) {
    return (n % m + m) % m;
}

void insert_hash(int *map, int value, int hash_size) {
    int hash_index = mod(value, hash_size);
    
    int count = 0;
    while(count++ < hash_size) {
        if(map[hash_index] == VALUE_NOTUSE) {
            map[hash_index] = value;
            break;
        }
        else {
            hash_index++;
            if(hash_index == hash_size) hash_index = 0;
        }
    }
}

bool search(int *map, int target, int hash_size) {
    int hash_index = mod(target, hash_size);
    int count = 0;
    while(count++ < hash_size) {
        if(map[hash_index] == target) return true;
        if(map[hash_index] == VALUE_NOTUSE) return false;

        hash_index++;
        if(hash_index == hash_size) hash_index = 0;
    }

    return false;
}


bool containsDuplicate(int* nums, int numsSize){
    int *hash_map = malloc(numsSize*sizeof(int));
    for(int i=0;i<numsSize;i++) {
        hash_map[i] = VALUE_NOTUSE;
    }
        
    for(int i=0;i<numsSize;i++) {
        if(search(hash_map, nums[i], numsSize)) {
            free(hash_map);
            return true;
        }
        else {
            insert_hash(hash_map, nums[i], numsSize);
        }
    }
    free(hash_map);
    
    return false;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%d\n", containsDuplicate(test_array, sizeof(test_array)/sizeof(int)));


}

