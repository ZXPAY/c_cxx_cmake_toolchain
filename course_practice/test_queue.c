#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

QUEUE_DEFINE(int, 10);


int main(int argc, char *argv[]) {

    queue_int_t queue01 = MY_QUEUE_INIT;

    for(int i=0;i<8;i++) {
        int wdata = i + 1;
        if(QUEUE_OK == offer_queue_int(&queue01, &wdata)) {
            printf("offer %d\n", wdata);
        }
        else {
            printf("offer queue fail\n");
        }
    }

    for(int i=0;i<6;i++) {
        int rdata = i + 1;
        if(QUEUE_OK == poll_queue_int(&queue01, &rdata)) {
            printf("poll %d\n", rdata);
        }
        else {
            printf("poll queue fail\n");
        }
    }


    for(int i=0;i<8;i++) {
        int wdata = i*10 + 1;
        if(QUEUE_OK == offer_queue_int(&queue01, &wdata)) {
            printf("offer %d\n", wdata);
        }
        else {
            printf("offer queue fail\n");
        }
    }
    
    for(int i=0;i<11;i++) {
        int rdata = i + 1;
        if(QUEUE_OK == poll_queue_int(&queue01, &rdata)) {
            printf("poll %d\n", rdata);
        }
        else {
            printf("poll queue fail\n");
        }
    }


}


