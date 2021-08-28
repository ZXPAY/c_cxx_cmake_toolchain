#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
 
*/

char TEST_SUDOKU[9][9] = 
    {{'5','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}};


bool isValidSudoku(char **board, int boardSize, int *boardColSize){
    *boardColSize = 9;

    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            printf("%c,", board[i][j]);
        }
        printf("\n");
    }

    return true;
}

int main() {
    printf("start\n");

    char **board_malloc = (char **) malloc(9 * sizeof(char *));

    for(int i=0;i<9;i++) {
        board_malloc[i] = (char *) malloc(9 * sizeof(char));
    }

    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            board_malloc[i][j] = TEST_SUDOKU[i][j];
        }
    }

    int board_col;
    printf("isValidSudoku: %d\n", isValidSudoku(board_malloc, 9, &board_col));
    
    free(board_malloc);
}

