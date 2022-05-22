#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define M 3
#define N 3
int test_matrix[M][N] = {
    {4,3,6},
    {3,4,5},
    {2,1,0}
};

const int dir[4][2] = {
    {1,0},
    {-1,0},
    {0,1},
    {0,-1}
};

int help_dfs(int **matrix, int **counts, int m, int *n, int r, int c) {
    if(counts[r][c]) return counts[r][c];

    int max_c = 1;
    printf("%d, %d\n", r, c);
    for(int i=0;i<4;i++) {
        int next_r = r + dir[i][0];
        int next_c = c + dir[i][1];
        if(next_r < m && next_r >= 0 && next_c < n[next_r] && next_c >= 0 && matrix[next_r][next_c] > matrix[r][c]) {
            int count = help_dfs(matrix, counts, m, n, next_r, next_c) + 1;
            if(max_c < count) max_c = count;
        }
    }
    counts[r][c] = max_c;

    return max_c;
}

int longestIncreasingPath(int **matrix, int matrixSize, int *matrixColSize) {
    int **counts = malloc(matrixSize*sizeof(int *));
    for(int i=0;i<matrixSize;i++) {
        counts[i] = malloc(matrixColSize[i]*sizeof(int));
        memset(counts[i], 0, matrixColSize[i]*sizeof(int));
    }

    int result = 0;

    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixColSize[i];j++) {
            int temp = help_dfs(matrix, counts, matrixSize, matrixColSize, i, j);
            if(result < temp) {
                result = temp;
            }
        }
    }

    printf("counts: \n");
    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixColSize[i];j++) {
            printf("%d,", counts[i][j]);
        }
        printf("\n");
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int **matrix = (int **)malloc(M*sizeof(int *));
    int *col = (int *)malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        matrix[i] = (int *)malloc(N*sizeof(int));
        memcpy(matrix[i], &test_matrix[i][0], N*sizeof(int));
        col[i] = N;
    }

    printf("result: %d\n", longestIncreasingPath(matrix, M, col));
}

