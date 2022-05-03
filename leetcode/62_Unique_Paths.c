#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 109.
*/

int uniquePaths_help(int **dp, int x, int y, int m, int n) {
    if(x+1 >= m || y+1 >= n) return 1;
    /* Search count from table */
    if(dp[x][y]) return dp[x][y];
    
    int k = 0;
    
    // Go right
    dp[x+1][y] = uniquePaths_help(dp, x+1, y, m, n);
    k += dp[x+1][y];
    
    // Go down
    dp[x][y+1] = uniquePaths_help(dp, x, y+1, m, n);
    k += dp[x][y+1];

    return k;
}

int uniquePaths(int m, int n) {
    /* start from (0, 0) to (m-1, n-1), only move right or down */
    int **dp = malloc(m*sizeof(int *));
    for(int i=0;i<m;i++) {
        dp[i] = malloc(n*sizeof(int));
        memset(dp[i], 0, n*sizeof(int));
    }
    
    dp[0][0] = uniquePaths_help(dp, 0, 0, m, n);

    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            printf("%4d,", dp[i][j]);
        }
        printf("\n");
    }


    return dp[0][0];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result[3x2]: %d\n\n", uniquePaths(3, 2));
    printf("result[3x3]: %d\n\n", uniquePaths(3, 3));
    printf("result[3x4]: %d\n\n", uniquePaths(3, 4));
    printf("result[3x7]: %d\n\n", uniquePaths(3, 7));
    printf("result[3x7]: %d\n\n", uniquePaths(5, 8));

}

