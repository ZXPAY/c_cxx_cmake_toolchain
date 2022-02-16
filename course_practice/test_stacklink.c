#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack_linklist.h"

STACKLINK_DEFINE(int);


int main(int argc, char *argv[]) {

    stacklink_int_t stacklink01 = {.head = NULL, .count = 0};

    for(int i=0;i<10;i++) {
        int tdata = i+1;
        if(STACKLINK_OK == push_stacklink_int(&stacklink01, &tdata)) {
            printf("push %d, count: %d\n", tdata, get_stacklink_size_int(&stacklink01));
        }
        else {
            printf("push fail\n");
        }
    }

    for(int i=0;i<3;i++) {
        int rdata;
        if(STACKLINK_OK == pop_stacklink_int(&stacklink01, &rdata)) {
            printf("pop %d, count: %d\n", rdata, get_stacklink_size_int(&stacklink01));
        }
        else {
            printf("pop fail\n");
        }
    }
    
    for(int i=0;i<5;i++) {
        int tdata = i+50;
        if(STACKLINK_OK == push_stacklink_int(&stacklink01, &tdata)) {
            printf("push %d, count: %d\n", tdata, get_stacklink_size_int(&stacklink01));
        }
        else {
            printf("push fail\n");
        }
    }
    
    for(int i=0;i<15;i++) {
        int rdata;
        if(STACKLINK_OK == pop_stacklink_int(&stacklink01, &rdata)) {
            printf("pop %d, count: %d\n", rdata, get_stacklink_size_int(&stacklink01));
        }
        else {
            printf("pop fail\n");
        }
    }

}



