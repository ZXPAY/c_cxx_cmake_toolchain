#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Design a HashMap without using any built-in hash table libraries.

Implement the MyHashMap class:

MyHashMap() initializes the object with an empty map.
void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.
 

Constraints:

0 <= key, value <= 106
At most 104 calls will be made to put, get, and remove.

*/

#define MAP_SIZE 1000001
typedef struct {
    int map[MAP_SIZE];
} MyHashMap;

MyHashMap *myHashMapCreate() {
    MyHashMap *obj = malloc(sizeof(MyHashMap));
    memset(obj, 0xFF, sizeof(MyHashMap));  // all value to -1

    return obj;
}

void myHashMapPut(MyHashMap *obj, int key, int value) {
    assert(key>=0);
    assert(value!=-1);
    obj->map[key] = value;
}

int myHashMapGet(MyHashMap *obj, int key) {
    return obj->map[key];
}

void myHashMapRemove(MyHashMap *obj, int key) {
    obj->map[key] = -1;
}

void myHashMapFree(MyHashMap *obj) {
    free(obj);    
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    MyHashMap* obj = myHashMapCreate();
    myHashMapPut(obj, 1, 1);
    myHashMapPut(obj, 2, 2);
    printf("%d\n", myHashMapGet(obj, 1)); // get 1
    printf("%d\n", myHashMapGet(obj, 3)); // get -1
    myHashMapPut(obj, 2, 1); // update
    printf("%d\n", myHashMapGet(obj, 2)); // get 1
    myHashMapRemove(obj, 2);
    printf("%d\n", myHashMapGet(obj, 2)); // get -1

    myHashMapFree(obj);
}

