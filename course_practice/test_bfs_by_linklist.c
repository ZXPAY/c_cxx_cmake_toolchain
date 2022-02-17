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


typedef struct _dblinklist_t {
    struct _dblinklist_t *left;
    struct _dblinklist_t *right;
    int val;
} dblinklist_t;


QUEUE_DEFINE(dblinklist_t, 10);


int test_array[] = {
    5, 2, 6, 1, 4, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0 
};
#define ARRAY_SIZE  ((sizeof(test_array) / sizeof(int)))

void bfs_handler(int value) {
    printf("%d, ", value);
}

void traverse_bfs(dblinklist_t *root) {
    queue_dblinklist_t_t myqueue = MY_QUEUE_INIT;

    offer_queue_dblinklist_t(&myqueue, root);

    while(true) {
        printf("size: %d\n", get_queue_size_dblinklist_t(&myqueue));
        if(get_queue_size_dblinklist_t(&myqueue) == 0) break;

        dblinklist_t tmp;
        poll_queue_dblinklist_t(&myqueue, &tmp);
        // if(tmp == NULL) continue;

        // printf("%d, %p, %p\n", tmp.val, tmp.left, tmp.right);
        bfs_handler(tmp.val);

        /* data flow */
        offer_queue_dblinklist_t(&myqueue, tmp.left);
        offer_queue_dblinklist_t(&myqueue, tmp.right);
    }

}


int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    /* Build the tree */
    dblinklist_t *node[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i++) {
        if(test_array[i] == 0) {
            node[i] = NULL;
            continue;
        }
        node[i] = (dblinklist_t *)malloc(sizeof(dblinklist_t));
        node[i]->left = NULL;
        node[i]->right = NULL;
        node[i]->val = test_array[i];
    }

    dblinklist_t *root = node[0];

    for(int i=0;i<ARRAY_SIZE-1;i++) {
        int i_left = (i + 1) * 2 - 1; 
        int i_right = (i + 1) * 2; 

        if(test_array[i] == 0) continue;

        dblinklist_t *temp = node[i];

        if(i_left < ARRAY_SIZE) {
            temp->left = node[i_left];            
        }
        if(i_right < ARRAY_SIZE) {
            temp->right = node[i_right];   
        }

    }

    printf("start BFS traverse\n");
    traverse_bfs(root);

    printf("end\n");

}
