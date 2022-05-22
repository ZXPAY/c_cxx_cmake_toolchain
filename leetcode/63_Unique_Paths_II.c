#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_grid[][3] = {{0,0,0},{0,1,0},{0,0,0}};

#define CONNECTION_SIZE_OF(x) (sizeof(x) / sizeof(x[0]))

#define OBSTACLE_VAL 1
int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize) {
    int **dp = (int **)malloc((obstacleGridSize+1)*sizeof(int *));
    int m = obstacleGridSize;
    int n = obstacleGridColSize[0];
    for(int i=0;i<=m;i++) {
        dp[i] = (int *)malloc((n+1)*sizeof(int *));
        memset(dp[i], 0, (n+1)*sizeof(int));
    }

    dp[0][1] = 1;
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) {
            if(obstacleGrid[i-1][j-1] != OBSTACLE_VAL) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    // for(int i=0;i<=m;i++) {
    //     for(int j=0;j<=n;j++) {
    //         printf("%2d,", dp[i][j]);
    //     }
    //     printf("\n");
    // }

    return dp[m][n];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int m = CONNECTION_SIZE_OF(test_grid);
    int **grid = malloc(m*sizeof(int *));
    int *grid_col = malloc(m*sizeof(int));
    for(int i=0;i<m;i++) {
        grid[i] = malloc(m*sizeof(int));
        memcpy(grid[i], &test_grid[i][0], m*sizeof(int));
        grid_col[i] = m;
    }
    printf("result: %d\n", uniquePathsWithObstacles(grid, m, grid_col));


}

