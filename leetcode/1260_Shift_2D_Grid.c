#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_array[3][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}};
// int test_array[7][1] = {
//     {1},
//     {2},
//     {3},
//     {4},
//     {7},
//     {6},
//     {5}};
#define K 3
#define M (sizeof(test_array) / sizeof(test_array[0]))
#define N (sizeof(test_array) / M / sizeof(int))

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **shiftGrid(int **grid, int gridSize, int *gridColSize, int k, int *returnSize, int **returnColumnSizes) {
    *returnColumnSizes = malloc(sizeof(int)*gridSize);
    *returnSize = gridSize;
    
    int grid_area = gridSize*(*gridColSize);

    int **grid_copy = malloc(sizeof(int *)*gridSize);
    for(int i=0;i<gridSize;i++) {
        grid_copy[i] = malloc(sizeof(int)*(*gridColSize));
        memcpy(grid_copy[i], &grid[i][0], sizeof(int)*(*gridColSize));
    }

    for(int i=0;i<gridSize;i++) {
        (*returnColumnSizes)[i] = *gridColSize;
        for(int j=0;j<*gridColSize;j++) {
            int temp = j + i*(*gridColSize) + k;
            temp %= grid_area;
            int m = temp / (*gridColSize);
            int n = temp % (*gridColSize);
            printf("%d, %d\n", m, n);
            grid_copy[m][n] = grid[i][j];
        }
    }

    return grid_copy;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **mat = malloc(sizeof(int *)*M);
    for(int i=0;i<M;i++) {
        mat[i] = malloc(sizeof(int)*N);
        memcpy(mat[i], &test_array[i][0], N*sizeof(int));
    }

    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            printf("%d, ", mat[i][j]);
        }
        printf("\n");
    }

    int return_size = 0;
    int col_size = N;
    int *return_col;
    int **result = shiftGrid(mat, M, &col_size, K, &return_size, &return_col);
    
    printf("===== result =====\n");
    for(int i=0;i<return_size;i++) {
        for(int j=0;j<return_col[i];j++) {
            printf("%d, ", result[i][j]);
        }
        printf("\n");
    }

}

