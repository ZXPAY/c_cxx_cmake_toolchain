#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.
*/

// const int test_grid[3][3] = {  // answer 4
//     {0,0,0},
//     {1,1,0},
//     {1,1,0}
// };
// const int test_grid[3][3] = {   // answer -1
//     {1,0,0},
//     {1,1,0},
//     {1,1,0}
// };
// const int test_grid[3][3] = {   // answer -1
//     {0,0,0},
//     {1,1,0},
//     {1,1,1}
// };
const int test_grid[3][3] = {   // answer 4
    {0,0,0},
    {0,1,0},
    {0,0,0}
};

// const int test_grid[6][6] = {   // answer 14
//     {0,1,1,0,0,0},
//     {0,1,0,1,1,0},
//     {0,1,1,0,1,0},
//     {0,0,0,1,1,0},
//     {1,1,1,1,1,0},
//     {1,1,1,1,1,0},
// };

#define N  3


typedef struct _pos_t {
    int r;
    int c;
    int distance;
    _pos_t *last_pos;
} pos_t;
typedef struct _save_pos {
    pos_t *pos;
    int len;
} save_pos_t;

int isInpos(save_pos_t *sv_pos, int row, int col) {
    for(int i=0;i<sv_pos->len;i++) {
        if(sv_pos->pos[i].r == row && sv_pos->pos[i].c == col) {
            return 1;
        }
    }
    return 0;
}

void save_pos(save_pos_t *sv_pos, int row, int col) {
    sv_pos->len++;
    sv_pos->pos = (pos_t *)realloc(sv_pos->pos, sizeof(pos_t)*sv_pos->len);
    sv_pos->pos[sv_pos->len-1].r = row;
    sv_pos->pos[sv_pos->len-1].c = col;
}

void pop_pos(save_pos_t *sv_pos, int *prow, int *pcol) {
    *prow = sv_pos->pos[0].r;
    *pcol = sv_pos->pos[0].c;
    for(int i=0;i<sv_pos->len-1;i++) {
        sv_pos->pos[i].r = sv_pos->pos[i+1].r;
        sv_pos->pos[i].c = sv_pos->pos[i+1].c;
    }
    sv_pos->len--;
    sv_pos->pos = (pos_t *)realloc(sv_pos->pos, sizeof(pos_t)*sv_pos->len);
}

void clean_pos(save_pos_t *sv_pos) {
    sv_pos->len = 0;
    free(sv_pos->pos);
}

void find_short(save_pos_t *sv_pos, int **grid, int row, int col, int gridSize, int distance, int *p_min_distance) {
    printf("=> %d, %d, distance: %d\n", row, col, distance);

    if(row+1 < gridSize && col+1 < gridSize) {
        if(grid[row+1][col+1] != 1) {    
            if(!isInpos(sv_pos, row+1, col+1)) {
                save_pos(sv_pos, row+1, col+1);
                find_short(sv_pos, grid, row+1, col+1, gridSize, distance+1, p_min_distance);
            }
        }
    } 
    if(row-1 >= 0 && col-1 >= 0) {
        if(grid[row-1][col-1] != 1) {      
            if(!isInpos(sv_pos, row-1, col-1)) {
                save_pos(sv_pos, row-1, col-1);
                find_short(sv_pos, grid, row-1, col-1, gridSize, distance+1, p_min_distance);
            }
        }
    }

    if(row+1 < gridSize && col-1 >= 0) {
        if(grid[row+1][col-1] != 1) {     
            if(!isInpos(sv_pos, row+1, col-1)) {
                save_pos(sv_pos, row+1, col-1);
                find_short(sv_pos, grid, row+1, col-1, gridSize, distance+1, p_min_distance);
            }
        }
    }
    if(row-1 >= 0 && col+1 < gridSize) {
        if(grid[row-1][col+1] != 1) {    
            if(!isInpos(sv_pos, row-1, col+1)) {
                save_pos(sv_pos, row-1, col+1);
                find_short(sv_pos, grid, row-1, col+1, gridSize, distance+1, p_min_distance);
            }
        }
    }

    if(row+1 < gridSize) {
        if(grid[row+1][col] != 1) {
            if(!isInpos(sv_pos, row+1, col)) {
                save_pos(sv_pos, row+1, col);
                find_short(sv_pos, grid, row+1, col, gridSize, distance+1, p_min_distance);
            }
        }
    }
    if(row-1 >= 0) {
        if(grid[row-1][col] != 1) {      
            if(!isInpos(sv_pos, row-1, col)) {
                save_pos(sv_pos, row-1, col);
                find_short(sv_pos, grid, row-1, col, gridSize, distance+1, p_min_distance);
            }
        }
    }
    if(col+1 < gridSize) {
        if(grid[row][col+1] != 1) {   
            if(!isInpos(sv_pos, row, col+1)) {
                save_pos(sv_pos, row, col+1);
                find_short(sv_pos, grid, row, col+1, gridSize, distance+1, p_min_distance);
            }
        }
    }
    if(col-1 >= 0) {
        if(grid[row][col-1] != 1) {    
            if(!isInpos(sv_pos, row, col-1)) {
                save_pos(sv_pos, row, col-1);
                find_short(sv_pos, grid, row, col-1, gridSize, distance+1, p_min_distance);
            }
        }
    }


    if(row == gridSize-1 && col == gridSize-1) {
        if(distance < *p_min_distance) {
            *p_min_distance = distance;
            clean_pos(sv_pos);
        }
    }
}

save_pos_t *search_nodes(int **grid, int row, int col, int gridSize) {
    save_pos_t *sv_pos = (save_pos_t *)malloc(sizeof(save_pos_t));
    sv_pos->len = 0;
    sv_pos->pos = NULL;

    // eight nearest neighbors
    int or = row;
    int oc = col;
    int nr = row - 1;
    int nc = col - 1;
    int pr = row + 1;
    int pc = col + 1;

    // up
    if(nr >= 0) {
        if(grid[nr][oc] == 0) {
            // continue;
            save_pos(sv_pos, nr, oc);
        }
    }
    // down
    if(pr < gridSize) {
        if(grid[pr][oc] == 0) {
            // continue;
            save_pos(sv_pos, pr, oc);
        }
    }
    // righ
    if(pc < gridSize) {
        if(grid[or][pc] == 0) {
            // continue;
            save_pos(sv_pos, or, pc);
        }
    }
    // left
    if(nc >= 0) {
        if(grid[or][nc] == 0) {
            // continue;
            save_pos(sv_pos, or, nc);
        }
    }
    // up-left
    if(nr >= 0 && nc >= 0) {
        if(grid[nr][nc] == 0) {
            // continue;
            save_pos(sv_pos, nr, nc);
        }
    }
    // up-right
    if(nr >= 0 && pc < gridSize) {
        if(grid[nr][pc] == 0) {
            // continue;
            save_pos(sv_pos, nr, pc);
        }
    }
    // down-left
    if(pr < gridSize && nc >= 0) {
        if(grid[pr][nc] == 0) {
            // continue;
            save_pos(sv_pos, pr, nc);
        }
    }
    // down-right
    if(pr < gridSize && pc < gridSize) {
        if(grid[pr][pc] == 0) {
            // continue;
            save_pos(sv_pos, pr, pc);
        }
    }
    return sv_pos;
}

int bfs_find_short(int **grid, int gridSize) {
    int end_flag = true;
    int lastr = 0, lastc = 0;
    int r = 0, c = 0;
    int distance = 0;
    int minus_distance = 0;
    int timeout_cnt = 0;
    save_pos_t seen = {
        .len = 0,
        .pos = NULL
    };
    save_pos_t sv_pos = {
        .len = 0,
        .pos = NULL
    };
    save_pos(&seen, 0, 0);
    save_pos(&sv_pos, 0, 0);

    // implement Dijkstra’s Shortest Path Algorithm
    while(sv_pos.len > 0) {
        pop_pos(&sv_pos, &r, &c);
        save_pos_t *nodes = search_nodes(grid, r, c, gridSize);

        for(int i=0;i<nodes->len;i++) {
            // printf(">>%d, %d\n", nodes->pos[i].r, nodes->pos[i].c);
            if(!isInpos(&seen, nodes->pos[i].r, nodes->pos[i].c)) {
                save_pos(&sv_pos, nodes->pos[i].r, nodes->pos[i].c);
                save_pos(&seen, nodes->pos[i].r, nodes->pos[i].c);
            }
        }
        printf("%d, %d\n", r, c);
    }
    return distance;
}

int shortestPathBinaryMatrix(int** grid, int gridSize, int* gridColSize) {
    // save_pos_t sv_pos = {
    //     .len = 0,
    //     .pos = NULL
    // };
    // save_pos(&sv_pos, 0, 0);

    // if(grid[0][0] == 1) {
    //     return -1;
    // }
    // int p_min_distance = __INT_MAX__;
    // find_short(&sv_pos, grid, 0, 0, gridSize, 1, &p_min_distance);
    // for(int i=0;i<sv_pos.len;i++) {
    //     printf(">>%d, %d\n", sv_pos.pos[i].r, sv_pos.pos[i].c);
    // }
    // if(p_min_distance == __INT_MAX__) return -1;
    // return p_min_distance;

    // Using BFS (Breadth-First Search)
    
    int dis = bfs_find_short(grid, gridSize);

    return dis;
}

int main() {
    printf("start \n");

    int **grid = (int *)malloc(N*sizeof(int));
    for(int i=0;i<N;i++) grid[i] = (int *)malloc(N*sizeof(int));

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            grid[i][j] = test_grid[i][j];
            printf("%d, ", grid[i][j]);
        }
        printf("\n");
    }

    int gridColSize = N;
    
    printf("shortestPathBinaryMatrix: %d\n", shortestPathBinaryMatrix(grid, N, &gridColSize));


    return 0;
}
