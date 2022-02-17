#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "queue.h"

/*
                5
        2               6
    1       4       X       7
   X X     3 X     X X     X  X

pre-order:  5, 2, 1, 4, 3, 6, 7
in-order:   1, 2, 3, 4, 5, 6, 7
post-order: 1, 3 ,4, 2, 7, 6, 5
*/


QUEUE_DEFINE(int, 10);


int test_array[] = {
    5, 2, 6, 1, 4, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0 
};
#define ARRAY_SIZE  ((sizeof(test_array) / sizeof(int)))

void bfs_handler(int value) {
    printf("%d, ", value);
}

void traverse_bfs(int *nums, int length) {
    queue_int_t myqueue = MY_QUEUE_INIT;

    int i_root = 0;
    offer_queue_int(&myqueue, &i_root);

    while(true) {
        if(get_queue_size_int(&myqueue) == 0) break;
        int i_poll = 0;
        poll_queue_int(&myqueue, &i_poll);

        if(i_poll >= length) continue;
        if(nums[i_poll] == 0) continue;

        bfs_handler(nums[i_poll]);

        /* data flow */
        int i_left = (i_poll + 1) * 2 - 1;
        int i_right = (i_poll + 1) * 2;

        offer_queue_int(&myqueue, &i_left);
        offer_queue_int(&myqueue, &i_right);

    }

}


int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("start BFS traverse\n");
    traverse_bfs(test_array, ARRAY_SIZE);
    printf("\n");
    printf("end\n");

}
