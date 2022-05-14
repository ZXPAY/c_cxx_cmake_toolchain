#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define M 3
#define N 3
int test_times[M][N] = {{2,1,1},{2,3,1},{3,4,1}}; // 2
#define TEST_N 4
#define TEST_K 2

// int test_times[M][N] = {{1,2,1},{2,3,2},{1,3,2}}; // 2
// #define TEST_N 3
// #define TEST_K 1

typedef int queue_data_t;

typedef enum queue_er_em {
    QUEUE_OK = 0,
    QUEUE_EMPTY = 1,
    QUEUE_FULL = 2,
    QUEUE_ERROR = 0xFF
} queue_er_em;

typedef struct _queue_t {
    queue_data_t *value;
    int buf_size;
    int offer_i;
    int poll_i;
    int count;
} queue_t;

queue_t *create_queue(int buf_size) {
    queue_t *queue = malloc(sizeof(queue_t));
    memset(queue, 0, sizeof(queue_t));
    queue->buf_size = buf_size;
    queue->value = malloc(buf_size*sizeof(queue_data_t));
    memset(queue->value, 0, buf_size*sizeof(queue_data_t));

    return queue;
}

queue_er_em offer_queue(queue_t *queue, queue_data_t *tdata) {
    if(queue->count >= queue->buf_size) return QUEUE_ERROR;
    memcpy(&queue->value[queue->offer_i++], tdata, sizeof(queue_data_t));
    if(queue->offer_i == queue->buf_size) queue->offer_i = 0;
    queue->count++;
    return QUEUE_OK;
}

queue_er_em poll_queue(queue_t *queue, queue_data_t *rdata) {
    if(queue->count < 1) return QUEUE_EMPTY;
    memcpy(rdata, &queue->value[queue->poll_i++], sizeof(queue_data_t));
    if(queue->poll_i == queue->buf_size) queue->poll_i = 0;
    queue->count--;
    return QUEUE_OK;
}

inline int get_queue_data_count(queue_t *queue) {
    return queue->count;
}

bool is_queue_empty(queue_t *queue) {
    return !(queue->count!=0);
}

int networkDelayTime(int **times, int timesSize, int *timesColSize, int n, int k) {
    /* Define the distance from start node */
    int *distance = (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) {
        distance[i] = INT32_MAX;
    }

    queue_t *buf = create_queue(n*4);

    /* Initialize the started k */
    int i_node = k-1; // start from 0
    distance[i_node] = 0;
    offer_queue(buf, &i_node);
    while(!is_queue_empty(buf)) {
        poll_queue(buf, &i_node);

        for(int i=0;i<timesSize;i++) {
            if(times[i][0]-1 != i_node) continue;

            int neighbor = times[i][1] - 1; // start from 0
            int t = times[i][2];
            int arrival = distance[i_node] + t;

            printf("%d->%d , arrival: %d\n", i_node+1, neighbor+1, arrival);

            if(distance[neighbor] > arrival) {
                distance[neighbor] = arrival;
                offer_queue(buf, &neighbor);
            }
        }
    }

    int result = 0;

    for(int i=0;i<n;i++) {
        printf("dis[%d]: %d\n", i+1, distance[i]);
        if(distance[i] == INT32_MAX) {
            return -1;
        }
        else if(distance[i] > result) {
            result = distance[i];
        }
    }

    if(result == 0) {
        return -1;
    }

    return result;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int **times = (int **)malloc(M*sizeof(int *));
    int *t_col = (int *)malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        times[i] = (int *)malloc(N*sizeof(int));
        memcpy(times[i], &test_times[i][0], N*sizeof(int));
        t_col[i] = N;
    }



    printf("result: %d\n", networkDelayTime(times, M, t_col, TEST_N, TEST_K));


}

