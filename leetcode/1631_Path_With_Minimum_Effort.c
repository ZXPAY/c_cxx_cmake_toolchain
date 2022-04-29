#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_heights[3][3] = {
    {1, 2, 2},
    {3, 8, 2},
    {5, 3, 5}
};

#define M (sizeof(test_heights) / sizeof(test_heights[0]))
#define N (sizeof(test_heights) / M / sizeof(int))

typedef struct {
    int row;
    int col;
    int height;
} node_t;

node_t *generate_node(int row, int col) {
    node_t *node = malloc(sizeof(node_t));
    node->row = row;
    node->col = col;
    node->height = 0;

    return node;
}



int go_maze(int **heights, int m, int n, node_t **node_buf, int *i_buf, int r_st, int c_st, int r_end, int c_end) {
    node_t *node_st = generate_node(r_st, c_st);
    node_t *node_end = generate_node(r_end, c_end);

    return go_maze_help(heights, m, n, node_buf, i_buf, node_st, node_end);
}
int a[10][10] = {0};
int go_maze_help(int **heights, int m, int n, node_t **node_buf, int *i_buf, node_t *node_st, node_t *node_end) {
    printf("%d=> \n", m);
    // Initialize the bufㄋ
    node_buf[(*i_buf)++] = node_st;

    while(*i_buf) {
        node_t *now_node = node_buf[--(*i_buf)];

        if(a[now_node->row][now_node->col] == 1) continue;
        a[now_node->row][now_node->col] = 1;
        printf("%d, %d, %d\n", *i_buf, now_node->row, now_node->col);

        /* explore next node */
        if(now_node->row-1 >= 0) {
            node_t *up = generate_node(now_node->row-1, now_node->col);
            node_buf[(*i_buf)++] = up;
        }
        if(now_node->row+1 < m) {
            node_t *down = generate_node(now_node->row+1, now_node->col);
            node_buf[(*i_buf)++] = down;
        }
        if(now_node->col-1 >= 0) {
            node_t *left = generate_node(now_node->row, now_node->col-1);
            node_buf[(*i_buf)++] = left;
        }
        if(now_node->col+1 < n) {
            node_t *right = generate_node(now_node->row, now_node->col+1);
            node_buf[(*i_buf)++] = right;
        }

    }


}

int minimumEffortPath(int **heights, int heightsSize, int *heightsColSize) {
    node_t **node_buf = malloc(heightsSize*(*heightsColSize)*10);
    int i_buf = 0;


    go_maze(heights, heightsSize, *heightsColSize, node_buf, &i_buf, 0, 0, 2, 2);


    return ;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **heights = malloc(M*sizeof(int *));
    for(int i=0;i<M;i++) {
        heights[i] = malloc(N*sizeof(int));
        memcpy(heights[i], &test_heights[i], N*sizeof(int));
    }

    int col_size = N;
    printf("result: %d\n", minimumEffortPath(heights, M, &col_size));

}

