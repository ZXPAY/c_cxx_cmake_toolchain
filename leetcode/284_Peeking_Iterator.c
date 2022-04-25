#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_arr[] = {1, 2, 3};
#define ARRAY_SIZE (sizeof(test_arr) / sizeof(int))
int count = 0;

typedef bool (*func_hasNext_t)(void);
typedef int (*func_next_t)(void);

bool arr_is_has_next() {
    if(count < ARRAY_SIZE) return true;
    return false;
}

int arr_next() {
    if(count < ARRAY_SIZE) return test_arr[count++];
    return -1;
}

struct Iterator {
    // Returns true if the iteration has more elements.
    bool (*hasNext)();
    // Returns the next element in the iteration.
    int (*next)();
};

struct PeekingIterator {
    struct Iterator *iterator;
    bool hasPeeked;
    int val;
};

struct Iterator *create_iterator(func_hasNext_t hasNext, func_next_t next) {
    struct Iterator *iter = malloc(sizeof(struct Iterator));
    iter->hasNext = hasNext;
    iter->next = next;

    return iter;
}

struct PeekingIterator *Constructor(struct Iterator* iter) {
    struct PeekingIterator *piter = malloc(sizeof(struct PeekingIterator));
    piter->iterator = iter;
    piter->hasPeeked = false;

    return piter;
}

int peek(struct PeekingIterator *obj) {
    if(obj->iterator->hasNext() && !obj->hasPeeked) {
        obj->val = obj->iterator->next();
        obj->hasPeeked = true;
    }
    return obj->val;
}

int next(struct PeekingIterator *obj) {
    if(!obj->hasPeeked && !obj->iterator->hasNext()) return -1;
    
    int next_val;
    if(obj->hasPeeked) {
        next_val = obj->val;
        if(obj->iterator->hasNext()) {
            obj->val = obj->iterator->next();
            obj->hasPeeked = true;
        }
        else {
            obj->hasPeeked = false;;
        }
    }
    else {
        next_val = obj->iterator->next();
        if(obj->iterator->hasNext()) {
            obj->val = obj->iterator->next();
            obj->hasPeeked = true;
        }
        else {
            obj->hasPeeked = false;
        }
    }
    
    return next_val;
}

bool hasNext(struct PeekingIterator* obj) {
    return obj->iterator->hasNext() || obj->hasPeeked;
}



int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct Iterator *iter = create_iterator(arr_is_has_next, arr_next);
    struct PeekingIterator *obj = Constructor(iter);
    printf("1 == %d\n", next(obj));
    printf("2 == %d\n", peek(obj));
    printf("2 == %d\n", next(obj));
    printf("3 == %d\n", next(obj));
    printf("0 == %d\n", hasNext(obj));

    return 0;
}

