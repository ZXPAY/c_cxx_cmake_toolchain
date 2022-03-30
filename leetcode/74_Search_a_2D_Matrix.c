#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_matrix[3][4] = {
    {1,3,5,7},
    {10,11,16,20},
    {23,30,34,60}};
#define TARGET 1


#define M  (sizeof(test_matrix) / sizeof(test_matrix[0]))
#define N  (sizeof(test_matrix) / M / sizeof(int))


bool search_help(int *matrix_row, int i_left, int i_right, int target) {
    if(i_left > i_right) return false;

    printf("%d, %d\n", i_left, i_right);

    int i_mid = (i_left + i_right) / 2;

    if(matrix_row[i_mid] == target) {
        return true;
    }
    else if(matrix_row[i_mid] > target) {
        // Go left
        return search_help(matrix_row, i_left, i_mid-1, target);        
    }
    else if(matrix_row[i_mid] < target) {
        // Go right
        return search_help(matrix_row, i_mid+1, i_right, target);
    }

    return false;
}


bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target) {
    // Find the row where target at
    int target_row = -1;
    for(int i=0;i<matrixSize;i++) {
        if(target <= matrix[i][(*matrixColSize)-1]) {
            target_row = i;
            break;
        }
    }
    if(target_row == -1) return false;
    printf("In row %d\n", target_row);

    return search_help(&matrix[target_row][0], 0, (*matrixColSize)-1, target);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("matrix size: %d, %d\n", M, N);


    int **matrix = malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        matrix[i] = malloc(N*sizeof(int));
        memcpy(matrix[i], &test_matrix[i][0], N*sizeof(int));
    }

    int col_size = N;
    printf("Result: %d\n", searchMatrix(matrix, M, &col_size, TARGET));

}

