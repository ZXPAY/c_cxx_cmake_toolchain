#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue_linklist.h"

QUEUELINK_DEFINE(int);


int main(int argc, char *argv[]) {

    queuelink_int_t queuelink01 = {.head = NULL, .tail = NULL, .count = 0};

    for(int i=0;i<10;i++) {
        int tdata = i+1;
        if(QUEUELINK_OK == offer_queuelink_int(&queuelink01, &tdata)) {
            printf("offer %d, count: %d\n", tdata, get_queuelink_size_int(&queuelink01));
        }
        else {
            printf("offer fail\n");
        }
    }

    for(int i=0;i<3;i++) {
        int rdata;
        if(QUEUELINK_OK == poll_queuelink_int(&queuelink01, &rdata)) {
            printf("poll %d, count: %d\n", rdata, get_queuelink_size_int(&queuelink01));
        }
        else {
            printf("poll fail\n");
        }
    }
    
    for(int i=0;i<5;i++) {
        int tdata = i+50;
        if(QUEUELINK_OK == offer_queuelink_int(&queuelink01, &tdata)) {
            printf("offer %d, count: %d\n", tdata, get_queuelink_size_int(&queuelink01));
        }
        else {
            printf("offer fail\n");
        }
    }
    
    for(int i=0;i<15;i++) {
        int rdata;
        if(QUEUELINK_OK == poll_queuelink_int(&queuelink01, &rdata)) {
            printf("poll %d, count: %d\n", rdata, get_queuelink_size_int(&queuelink01));
        }
        else {
            printf("poll fail\n");
        }
    }

}



