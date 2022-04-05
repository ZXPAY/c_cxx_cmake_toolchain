#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[3][3] =
//     {{1,2,3},
//     {4,5,6},
//     {7,8,9}};
int test_array[4][4] =
    {{1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}};

#define N   (sizeof(test_array) / sizeof(test_array[0]))



int diagonalSum(int **mat, int matSize, int* matColSize){
    int i = 0; // row
    int j = 0; // col
    int sum_val = 0;
    *matColSize = matSize;
    while(i < matSize) {
        // printf("%d, %d   %d\n", i, j, matSize-1-j);
        sum_val += mat[i][j] + mat[i][matSize-1-j];
        i++;
        j++;
    }
    if(matSize & 1) {
        // odd
        sum_val -= mat[matSize>>1][matSize>>1];
    }

    return sum_val;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int col_size;

    int **mat = malloc(N*sizeof(int *));

    for(int i=0;i<N;i++) {
        mat[i] = malloc(N*sizeof(int));
        memcpy(mat[i], &test_array[i][0], N*sizeof(int));
    }

    printf("result: %d\n", diagonalSum(mat, N, &col_size));


}

