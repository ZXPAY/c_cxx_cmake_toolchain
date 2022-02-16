#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"


/* Generate the stack type and length start */
STACK_DEFINE(int, 100);


typedef struct _mydata_t {
    int a;
    int b;
} mydata_t;
STACK_DEFINE(mydata_t, 100);
/* Generate the stack type and length end */

int main(int argc, char *argv[]) {
    printf("start\n");

    stack_int_t stack01 = MY_STACK_INIT;

    for(int i=0;i<5;i++) {
        int wdata = i+1;
        if(STACK_OK == push_stack_int(&stack01, &wdata)) {
            printf("%d\n", get_stack_size_int(&stack01));
        }
        else {
            printf("push stack fail\n");
        }
    }

    for(int i=0;i<6;i++) {
        int data;
        if(STACK_OK == pop_stack_int(&stack01, &data)) {
            printf("pop: %d\n", data);
        }
        else {
            printf("pop statck fail\n");
        }
    }

    /* another type */
    stack_mydata_t_t stack02 = MY_STACK_INIT;

    for(int i=0;i<10;i++) {
        mydata_t data;
        data.a = i+10;
        data.b = i*i*2 + i*3;
        if(STACK_OK == push_stack_mydata_t(&stack02, &data)) {
            printf("push: a: %d, b: %d\n", data.a, data.b);
        }
        else {
            printf("push stack fail\n");
        }
    }

    for(int i=0;i<11;i++) {
        mydata_t data;
        if(STACK_OK == pop_stack_mydata_t(&stack02, &data)) {
            printf("pup: a: %d, b: %d\n", data.a, data.b);
        }
        else {
            printf("pop stack fail\n");
        }
    }


}

