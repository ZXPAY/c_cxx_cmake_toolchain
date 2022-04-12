#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_board[4][3] = {
    {0,1,0},
    {0,0,1},
    {1,1,1},
    {0,0,0},
};

#define M (sizeof(test_board) / sizeof(test_board[0]))
#define N (sizeof(test_board) / M / sizeof(int))


#define DEAD_CELL  0
#define ALIVE_CELL 1
int Conway_cell_logic(int **board, int r, int c, int m, int n) {
    int eight_count = 0;
    int result = board[r][c];
    if(r+1 < m)  eight_count += board[r+1][c];
    if(r-1 >= 0) eight_count += board[r-1][c];
    if(c+1 < n)  eight_count += board[r][c+1];
    if(c-1 >= 0) eight_count += board[r][c-1];
    if(r+1 < m && c+1 < n)   eight_count += board[r+1][c+1];
    if(r+1 < m && c-1 >= 0)  eight_count += board[r+1][c-1];
    if(r-1 >= 0 && c+1 < n)  eight_count += board[r-1][c+1];
    if(r-1 >= 0 && c-1 >= 0) eight_count += board[r-1][c-1];
    
    if(eight_count < 2) {
        if(board[r][c] == ALIVE_CELL) {
            result = DEAD_CELL;
        }
    }
    else if(eight_count == 3) {
        if(board[r][c] == DEAD_CELL) {
            // Alive the dead cell
            result = ALIVE_CELL;
        }
    }
    else if(eight_count > 3) {
        result = DEAD_CELL;
    }

    return result;
}

void gameOfLife(int **board, int boardSize, int *boardColSize) {
    // Copy the board
    int **board_copy = malloc(sizeof(int *)*M);
    for(int i=0;i<M;i++) {
        board_copy[i] = malloc(sizeof(int)*N);
        memcpy(board_copy[i], &board[i][0], sizeof(int)*N);
    }

    for(int i=0;i<boardSize;i++) {
        for(int j=0;j<*boardColSize;j++) {
            board[i][j] = Conway_cell_logic(board_copy, i, j, boardSize, *boardColSize);
        }
    }

    free(board_copy);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **board = malloc(sizeof(int *)*M);
    for(int i=0;i<M;i++) {
        board[i] = malloc(sizeof(int)*N);
        memcpy(board[i], &test_board[i][0], sizeof(int)*N);
    }

    int col_size = N;
    printf("===== Before =====\n");
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
    
    gameOfLife(board, M, &col_size);

    printf("===== After =====\n");
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }

}

