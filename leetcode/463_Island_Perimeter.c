#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int grid[4][4] = {
    {0,1,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {1,1,0,0}
};

// int grid[4][3] = {
//     {0,1,0},
//     {1,1,0},
//     {0,1,0},
//     {1,1,0}
// };

void cpyGridToHeap(int **grid_dst, int *grid_src, int row, int col) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            (*grid_dst)[j] = *(grid_src + i*col + j);
            printf("%d, ", *(grid_src + i*col + j));
        }
        printf("\n");
        grid_dst++;
    }
}


int islandPerimeter(int** grid, int gridSize, int* gridColSize) {
    for(int i=0;i<gridSize;i++) {
        for(int j=0;j<*gridColSize;j++) {
            
        }
        grid++;
    }
    
    return 0;
}

int main() {
    printf("grid (%p) size: %d\n", grid, sizeof(grid));
    int row = sizeof(grid) / sizeof(grid[0]);
    int col = sizeof(grid[0])/row;
    printf("row: %d, col:%d\n", row, col);

    int **arr = (int **)malloc(row * sizeof(int *));
    for (int i=0; i<4; i++)
         arr[i] = (int *)malloc(col * sizeof(int));

    printf("copy the data to heap\n");
    cpyGridToHeap(arr, (int *)grid, row, col);
        
    printf("start algorithm\n");
    printf("Perimeter: %d\n", islandPerimeter(arr, 4, &col));

    return 0;
}

