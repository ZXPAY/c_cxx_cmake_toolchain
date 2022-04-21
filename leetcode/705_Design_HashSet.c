#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef struct {
    uint32_t map[32000];
    uint32_t set_count;
} MyHashSet;

int mod(int n, int m) {
    return (n % m + m) % m;
}

MyHashSet* myHashSetCreate() {
    MyHashSet *hash_set = malloc(sizeof(MyHashSet));
    memset(hash_set, 0, sizeof(MyHashSet));

    return hash_set;
}

void myHashSetAdd(MyHashSet *obj, int key) {
    assert(key<32*32000);
    int n = key / 32;
    int i = mod(key, 32);
    obj->map[n] |= (1U << i);
}

void myHashSetRemove(MyHashSet *obj, int key) {
    assert(key<32*32000);
    int n = key / 32;
    int i = mod(key, 32);
    obj->map[n] &= ~(1U << i);
}

bool myHashSetContains(MyHashSet *obj, int key) {
    assert(key<32*32000);
    int n = key / 32;
    int i = mod(key, 32);
    if(obj->map[n] & (1U<<i)) return true;
    return false;
}

void myHashSetFree(MyHashSet *obj) {
    free(obj);
}


int main(int argc, char *argv[]) {

    MyHashSet* obj = myHashSetCreate();
    myHashSetAdd(obj, 1);
    myHashSetAdd(obj, 2);
    printf("T contain 2 ?: %d\n", myHashSetContains(obj, 2));
    printf("F contain 3 ?: %d\n", myHashSetContains(obj, 3));
    myHashSetAdd(obj, 2);
    printf("T contain 2 ?: %d\n", myHashSetContains(obj, 2));
    printf("Remove 2\n");
    myHashSetRemove(obj, 2);
    printf("F contain 2 ?: %d\n", myHashSetContains(obj, 2));
    myHashSetFree(obj);



}

