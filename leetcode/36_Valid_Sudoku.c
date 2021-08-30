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

// char TEST_SUDOKU[9][9] = 
//     {{'5','3','.','.','7','.','.','.','.'}
//     ,{'6','.','.','1','9','5','.','.','.'}
//     ,{'.','9','8','.','.','.','.','6','.'}
//     ,{'8','.','.','.','6','.','.','.','3'}
//     ,{'4','.','.','8','.','3','.','.','1'}
//     ,{'7','.','.','.','2','.','.','.','6'}
//     ,{'.','6','.','.','.','.','2','8','.'}
//     ,{'.','.','.','4','1','9','.','.','5'}
//     ,{'.','.','.','.','8','.','.','7','9'}};

char TEST_SUDOKU[9][9] = 
    {{'.','.','.','.','.','.','.','.','.'}
    ,{'.','.','.','.','.','.','.','.','.'}
    ,{'.','9','.','.','.','.','.','.','1'}
    ,{'8','.','.','.','.','.','.','.','.'}
    ,{'.','9','9','3','5','7','.','.','.'}
    ,{'.','.','.','.','.','.','.','4','.'}
    ,{'.','.','.','8','.','.','.','.','.'}
    ,{'.','1','.','.','.','.','4','.','9'}
    ,{'.','.','.','5','.','4','.','.','.'}};

bool isValidSudoku(char **board, int boardSize, int *boardColSize){
    *boardColSize = 9;

    int *hash_col = (int *)malloc(10*sizeof(int));
    memset(hash_col, 0, 10*sizeof(int));
    int *hash_row = (int *)malloc(10*sizeof(int));
    memset(hash_row, 0, 10*sizeof(int));

    char temp_c, temp_r;
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            temp_c = board[i][j];
            temp_r = board[j][i];
            if(temp_c != '.') {
                hash_col[temp_c-'0']++;
            }
            if(temp_r != '.') {
                hash_row[temp_r-'0']++;
            }
        }
        for(int k=0;k<10;k++) {
            if(hash_col[k] > 1) {
                return false;
            }
            if(hash_row[k] > 1) {
                return false;
            }
        }
        memset(hash_col, 0, 10*sizeof(int));
        memset(hash_row, 0, 10*sizeof(int));
    }

    // check 3x3
    char temp_33;
    int *hash_33 = (int *)malloc(10*sizeof(int));
    memset(hash_33, 0, 10*sizeof(int));
    for(int i=0;i<9;i+=3) {
        for(int j=0;j<9;j+=3) {
            for(int w=i;w<i+3;w++) {
                for(int q=j;q<j+3;q++) {
                    temp_33 = board[w][q];
                    if(temp_33 != '.') {
                        hash_33[temp_33-'0']++;
                    }
                }
            }
            for(int k=0;k<10;k++) {
                if(hash_33[k] > 1) {
                    return false;
                }
            }
            memset(hash_33, 0, 10*sizeof(int));
        }
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

