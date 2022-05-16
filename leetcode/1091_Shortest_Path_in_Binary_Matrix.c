#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


#define M 3
#define N 3
int matrix[3][3] = {{0,0,0},{1,1,0},{1,1,0}};

typedef struct _pair_t {
    int x;
    int y;
} pair_t;

typedef pair_t queue_data_t;

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
    assert(queue->count < queue->buf_size);
    if(queue->count >= queue->buf_size) return QUEUE_ERROR;
    memcpy(&queue->value[queue->offer_i++], tdata, sizeof(queue_data_t));
    if(queue->offer_i == queue->buf_size) queue->offer_i = 0;
    queue->count++;
    return QUEUE_OK;
}

queue_er_em poll_queue(queue_t *queue, queue_data_t *rdata) {
    assert(queue->count > 0);
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

int shortestPathBinaryMatrix(int **grid, int gridSize, int *gridColSize) {
    if(grid[0][0] == 1) return -1;

    queue_t *buf = create_queue(500);
    int dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

    pair_t pair = {
        .x = 0,
        .y = 0
    };
    pair_t temp;
    int count = 0;
    offer_queue(buf, &pair);

    while(!is_queue_empty(buf)) {
        int c = get_queue_data_count(buf);
        count++;
        for(int i=0;i<c;i++) {
            poll_queue(buf, &pair);
            // printf("%d, %d\n", pair.x, pair.y);
            if(pair.x == gridSize-1 && pair.y == gridColSize[0]-1) {
                return count;
            }
            for(int j=0;j<8;j++) {
                int tr = pair.x + dir[j][0];
                int tc = pair.y + dir[j][1];
                if(tr>=0 && tr<gridSize && tc>=0 && tc<gridColSize[0] && grid[tr][tc] == 0) {
                    temp.x = tr;
                    temp.y = tc;
                    offer_queue(buf, &temp);

                    grid[tr][tc] = -1;
                }
            }
        }
    }

    return -1;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **grid = (int **)malloc(M*sizeof(int));
    int *grid_col = (int *)malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        grid[i] = (int *)malloc(N*sizeof(int));
        memcpy(grid[i], &matrix[i][0], N*sizeof(int));
        grid_col[i] = 3;
    }

    printf("result: %d\n", shortestPathBinaryMatrix(grid, M, grid_col));



}

