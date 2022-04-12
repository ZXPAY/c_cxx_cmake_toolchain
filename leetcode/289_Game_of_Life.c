#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the m x n grid board, return the next state.
*/

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
        // 1 -> 0
        if(board[r][c] == ALIVE_CELL) {
            result = DEAD_CELL;
        }
    }
    else if(eight_count == 3) {
        // 0 -> 1
        if(board[r][c] == DEAD_CELL) {
            // Alive the dead cell
            result = ALIVE_CELL;
        }
    }
    else if(eight_count > 3) {
        // x -> 0
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

/* Solution 2, Space complexity is O(1) */
#define CASE_ONE_TO_ZERO    2    // previous is one
#define CASE_ZERO_TO_ONE    3    // previous is zero
const int eight_dir[8][2] = {
    {-1,-1},
    {-1, 0},
    {-1, 1},
    { 0, 1},
    { 1, 1},
    { 1, 0},
    { 1,-1},
    { 0,-1},
};
int Conway_cell_logic2(int **board, int r, int c, int m, int n) {
    int eight_count = 0;
    for(int i=0;i<8;i++) {
        int nr = r + eight_dir[i][0];
        int nc = c + eight_dir[i][1];
        if(nr < 0 || nc < 0 || nr > (m-1) || nc > (n-1)) continue;

        if(board[nr][nc] == CASE_ONE_TO_ZERO || board[nr][nc] == ALIVE_CELL) {
            eight_count++;
        }
    }
    
    int result = board[r][c];
    if(eight_count < 2) {
        // 1 -> 0
        if(board[r][c] == ALIVE_CELL) {
            result = CASE_ONE_TO_ZERO;
        }
    }
    else if(eight_count == 3) {
        // 0 -> 1
        if(board[r][c] == DEAD_CELL) {
            // Alive the dead cell
            result = CASE_ZERO_TO_ONE;
        }
    }
    else if(eight_count > 3) {
        // 1 -> 0
        if(board[r][c] == ALIVE_CELL) {
            result = CASE_ONE_TO_ZERO;
        }
    }

    return result;
}

void gameOfLife2(int **board, int boardSize, int *boardColSize) {
    // Copy the board
    for(int i=0;i<boardSize;i++) {
        for(int j=0;j<*boardColSize;j++) {
            // iterate the board[i][j]
            board[i][j] = Conway_cell_logic2(board, i, j, boardSize, *boardColSize);
        }
    }

    // update the board[i][j] to 0 or 1
    for(int i=0;i<boardSize;i++) {
        for(int j=0;j<*boardColSize;j++) {
            if(CASE_ONE_TO_ZERO == board[i][j]) {
                board[i][j] = 0;
            }
            else if(CASE_ZERO_TO_ONE == board[i][j]) {
                board[i][j] = 1;
            }
        }
    }
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
    
    // gameOfLife(board, M, &col_size);
    gameOfLife2(board, M, &col_size);

    printf("===== After =====\n");
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }

}

