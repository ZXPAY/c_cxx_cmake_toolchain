#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


#define STACK_SIZE 100

typedef struct {
    int *value;
    int count;
} MyStack;


MyStack* myStackCreate() {
    MyStack *stack = malloc(sizeof(MyStack));
    memset(stack, 0, sizeof(MyStack));
    stack->value = malloc(sizeof(int)*STACK_SIZE);
    memset(stack->value, 0, sizeof(MyStack));

    return stack;
}

void myStackPush(MyStack* obj, int x) {
    obj->value[obj->count++] = x;
}

int myStackPop(MyStack* obj) {
    if(obj->count<=0) return -1;
    int temp = obj->value[--obj->count];

    return temp;
}

int myStackTop(MyStack* obj) {
    if(obj->count<=0) return -1;
    return obj->value[obj->count-1];
}

bool myStackEmpty(MyStack* obj) {
    if(obj->count<=0) return true;

    return false;
}

void myStackFree(MyStack* obj) {
    free(obj->value);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    MyStack *myStack = myStackCreate();
    myStackPush(myStack, 1);
    myStackPush(myStack, 2);
    int val1 = myStackTop(myStack);   // return 2
    printf("val1: %d\n", val1);
    
    int val2 = myStackPop(myStack);   // return 2
    printf("val2: %d\n", val2);
    
    int val3 = myStackEmpty(myStack); // return false
    printf("val3: %d\n", val3);


    myStackFree(myStack);

}

