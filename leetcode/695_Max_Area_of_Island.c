#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.
*/

#define M  8
#define N  13

int test_area[M][N] = {
    {0,0,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,1,1,0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,1,1,0,0,1,0,1,0,0},
    {0,1,0,0,1,1,0,0,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0}};

#define STEPPED -1
int maxAreaOfIsland_help(int **grid, int m, int n, int x, int y) {
    if(x<0 || x>=m) return 0;
    if(y<0 || y>=n) return 0;
    if(grid[x][y] == 0) {
        grid[x][y] = STEPPED;
        return 0;
    }
    if(grid[x][y] == STEPPED) return 0;

    grid[x][y] = STEPPED;

    // left
    int left_count = maxAreaOfIsland_help(grid, m, n, x-1, y);

    // right
    int right_count = maxAreaOfIsland_help(grid, m, n, x+1, y);

    // down
    int down_count = maxAreaOfIsland_help(grid, m, n, x, y-1);

    // up
    int up_count = maxAreaOfIsland_help(grid, m, n, x, y+1);

    return 1 + left_count + right_count + down_count + up_count;
}

int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize){
    int best_count = 0;
    for(int i=0;i<gridSize;i++) {
        for(int j=0;j<*gridColSize;j++) {
            int temp = maxAreaOfIsland_help(grid, gridSize, *gridColSize, i, j);
            if(temp > best_count) {
                best_count = temp;
            }
        }
    }

    return best_count;
}

int main(int argc, char *argv[]) {
    int **grid = malloc(sizeof(int)*M);

    for(int i=0;i<M;i++) {
        grid[i] = malloc(sizeof(int)*N);
    }

    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            grid[i][j] = test_area[i][j];
        }
    }

    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            printf("%d,", grid[i][j]);
        }
        printf("\n");
    }

    int col_size = N;
    printf("maxAreaOfIsland: %d\n", maxAreaOfIsland(grid, M, &col_size));
}

