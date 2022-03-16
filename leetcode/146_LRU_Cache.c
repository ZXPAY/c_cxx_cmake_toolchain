#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.
*/

typedef struct _key_val_t {
    int key;
    int value;
} key_value_t;

typedef struct {
    key_value_t *key_value;
    int *used_count;
    int count;
    int capacity;    
} LRUCache;

LRUCache *lRUCacheCreate(int capacity) {
    LRUCache *lru_cache = malloc(sizeof(LRUCache));
    key_value_t *key_value = malloc(sizeof(key_value_t)*capacity);    
    int *used_count = malloc(sizeof(int)*capacity);    
    memset(lru_cache, 0, sizeof(LRUCache));
    memset(key_value, 0, sizeof(key_value_t)*capacity);
    memset(used_count, 0, sizeof(int)*capacity);

    lru_cache->capacity = capacity;
    lru_cache->key_value = key_value;
    lru_cache->used_count = used_count;
    return lru_cache;
}

int lRUCacheGet(LRUCache *obj, int key) {
    for(int i=0;i<obj->count;i++) {
        if(obj->key_value[i].key == key) {
            obj->used_count[i]++;
            return obj->key_value[i].value;
        }
    }

    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
    for(int i=0;i<obj->count;i++) {
        if(obj->key_value[i].key == key) {
            obj->key_value[i].value = value;
            return;
        }
    }
    if(obj->count < obj->capacity) {
        obj->key_value[obj->count].key = key;
        obj->key_value[obj->count++].value = value;
    }
    else {

    }
}

void lRUCacheFree(LRUCache *obj) {
    free(obj);    
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/

int main(int argc, char *argv[]) {
    LRUCache *lRUCache = lRUCacheCreate(2);
    lRUCachePut(lRUCache, 1, 1);            // cache is {1=1}
    lRUCachePut(lRUCache, 2, 2);            // cache is {1=1, 2=2}
    int val1 = lRUCacheGet(lRUCache, 1);    // return 1
    lRUCachePut(lRUCache, 3, 3);            // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    int val2 = lRUCacheGet(lRUCache, 2);    // returns -1 (not found)
    lRUCachePut(lRUCache, 4, 4);            // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    int val3 = lRUCacheGet(lRUCache, 1);    // return -1 (not found)
    int val4 = lRUCacheGet(lRUCache, 3);    // return 3
    int val5 = lRUCacheGet(lRUCache, 4);    // return 4

    /*
    ans: 1,-1,-1,3,4
    */
    printf("%d\n", val1);
    printf("%d\n", val2);
    printf("%d\n", val3);
    printf("%d\n", val4);
    printf("%d\n", val5);

}

