#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define N  10

/*
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
*/

typedef enum _state {
    STATE_RIGHT = 0,
    STATE_DOWN = 1,
    STATE_LEFT = 2,
    STATE_UP = 3,
} go_state_nm;


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes){
    int **matrix = malloc(n*sizeof(int *));
    *returnSize = n;
    // **returnColumnSizes = n;
    *returnColumnSizes = malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) {
        matrix[i] = malloc(n*sizeof(int));
        memset(matrix[i], 0, n*sizeof(int));
        *((*returnColumnSizes)+i) = n;
    }

    go_state_nm state = STATE_RIGHT;
    int count = 2;
    int c = 0;
    int r = 0;
    matrix[0][0] = 1;
    while(count <= n*n) {
        // printf("[%d, %d], %d, %d\n", r, c, count, state);
        switch (state) {
            case STATE_RIGHT:
                // boundary check
                if(c+1 < n) {
                    if(matrix[r][c+1] == 0) {
                        matrix[r][c+1] = count;
                        c++;
                    }
                    else {
                        // already feed the value
                        // go down
                        state = STATE_DOWN;
                        continue;
                    }
                }
                else {
                    // boundary handle
                    // go down
                    state = STATE_DOWN;
                    continue;
                }
                break;
            case STATE_DOWN:
                // boundary check
                if(r+1 < n) {
                    if(matrix[r+1][c] == 0) {
                        matrix[r+1][c] = count;
                        r++;
                    }
                    else {
                        // already feed the value
                        // go left
                        state = STATE_LEFT;
                        continue;
                    }
                }
                else {
                    // boundary handle
                    // go left
                    state = STATE_LEFT;
                    continue;
                }
                break;
            case STATE_LEFT:
                // boundary check
                if(c-1 >= 0) {
                    if(matrix[r][c-1] == 0) {
                        matrix[r][c-1] = count;
                        c--;
                    }
                    else {
                        // already feed the value
                        // go up
                        state = STATE_UP;
                        continue;
                    }
                }
                else {
                    // boundary handle
                    // go up
                    state = STATE_UP;
                    continue;
                }
                break;
            case STATE_UP:
                // boundary check
                if(r-1 >= 0) {
                    if(matrix[r-1][c] == 0) {
                        matrix[r-1][c] = count;
                        r--;
                    }
                    else {
                        // already feed the value
                        // go right
                        state = STATE_RIGHT;
                        continue;
                    }
                }
                else {
                    // boundary handle
                    // go right
                    state = STATE_RIGHT;
                    continue;
                }
                break;
            default:
                assert(0);
                break;
        }

        count++;
    }

    return matrix;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_size;
    int *return_col = malloc(sizeof(int));
    int **matrix = generateMatrix(N, &return_size, &return_col);

    printf("===== Matrix =====\n");
    for(int i=0;i<return_size;i++) {
        for(int j=0;j<N;j++) {
            printf("%3d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

