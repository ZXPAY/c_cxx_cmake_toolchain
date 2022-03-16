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

typedef struct _dblinklist_t {
    struct _dblinklist_t *next;
    struct _dblinklist_t *prev;
    int key;
    int value;
} dblinklist_t;

typedef struct {
    dblinklist_t *root;
    int count;
    int capacity;
} LRUCache;

dblinklist_t *create_node(int key, int value) {
    dblinklist_t *node = malloc(sizeof(dblinklist_t));
    memset(node, 0, sizeof(dblinklist_t));
    node->key = key;
    node->value = value;

    printf("%p: %d\n", node, node->key);

    return node;
}

LRUCache *lRUCacheCreate(int capacity) {
    LRUCache *lru_cache = malloc(sizeof(LRUCache));
    memset(lru_cache, 0, sizeof(LRUCache));
    lru_cache->capacity = capacity;

    return lru_cache;
}

int lRUCacheGet(LRUCache *obj, int key) {
    dblinklist_t *temp = obj->root;
    int result = -1;
    while(temp != NULL) {
        if(temp->key == key) {
            result = temp->value;
            break;
        }
        temp = temp->next;
    }

    if(temp != NULL) {
        dblinklist_t *target_next = temp->next;
        dblinklist_t *target_prev = temp->prev;
        printf("%p, %p, %p\n", temp, target_next, target_prev);
        if(target_next != NULL) {
            target_next->prev = target_prev;
        }
        if(target_prev != NULL) {
            target_prev->next = target_next;
        }
        if(obj->root != temp) {
            obj->root->prev = temp;
            temp->next = obj->root;
            obj->root = temp;
        }
    }
    printf("%p, %p\n", obj->root, obj->root->next);

    return result;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
    dblinklist_t *temp = obj->root;
    dblinklist_t *last_node = temp;
    while(temp != NULL) {
        if(temp->key == key) {
            temp->value = value;
            return;
        }
        last_node = temp;
        temp = temp->next;
    }
    if(obj->count < obj->capacity) {
        if(obj->count == 0) {
            obj->root = create_node(key, value);
        }
        else {
            last_node->next = create_node(key, value);
            last_node->next->prev = last_node;
        }
        obj->count++;
    }
    else {
        dblinklist_t *new_root = create_node(key, value);
        obj->root->prev = new_root;
        new_root->next = obj->root;
        obj->root = new_root;
        if(last_node->prev != NULL)
            last_node->prev->next = NULL;
        printf("%d\n", last_node->value);
        free(last_node);
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
    printf("===\n");
    lRUCachePut(lRUCache, 4, 4);            // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    int val3 = lRUCacheGet(lRUCache, 1);    // return -1 (not found)
    int val4 = lRUCacheGet(lRUCache, 3);    // return 3
    int val5 = lRUCacheGet(lRUCache, 4);    // return 4

    /*
    ans: 1,-1,-1,3,4
    */
    // printf("%d\n", val1);
    // printf("%d\n", val2);
    // printf("%d\n", val3);
    // printf("%d\n", val4);
    // printf("%d\n", val5);

}

