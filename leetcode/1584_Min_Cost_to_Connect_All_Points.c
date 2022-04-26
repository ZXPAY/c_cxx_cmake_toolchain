#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* ans=20 */
int test_points[][2] = {{0,0},{2,2},{3,10},{5,2},{7,0}};

/* ans=18 */
// int test_points[][2] = {{3,12},{-2,5},{-4,1}};

#define POINT_LEN (sizeof(test_points) / sizeof(test_points[0]))

int abs_int(int x) {
    if(x < 0) return -x;
    return x;
}

int cal_manhattan_distance(int **points, int i_p1, int i_p2, int **dp) {
    if(dp[i_p1][i_p2] != -1) return dp[i_p1][i_p2];
    int x1 = points[i_p1][0];
    int x2 = points[i_p2][0];
    int y1 = points[i_p1][1];
    int y2 = points[i_p2][1];
    int dis = abs_int(x1 - x2) + abs_int(y1 - y2);
    // save to dp
    dp[i_p1][i_p2] = dis;
    return dis;
}

int minCostConnectPoints(int **points, int pointsSize, int *pointsColSize) {
    // Dynamic programming, build search table
    int **dp = malloc(pointsSize*sizeof(int *));
    for(int i=0;i<pointsSize;i++) {
        dp[i] = malloc(pointsSize*sizeof(int));
        memset(dp[i], 0xFF, pointsSize*sizeof(int)); // default table is -1
    }
    bool *visited = malloc(pointsSize*sizeof(bool));
    memset(visited, 0, pointsSize*sizeof(bool));
    int *min_costs = malloc(pointsSize*sizeof(int));
    for(int i=0;i<pointsSize;i++) {
        min_costs[i] = INT32_MAX;
    }

    // Prim algorithm
    int result = 0;
    int cur = 0;
    while(cur >= 0) {
        int next = -1;
        int cur_min = INT32_MAX;
        visited[cur] = true;
        
        // find the minimal distance to other points
        for(int i=0;i<pointsSize;i++) {
            if(visited[i] || cur == i) continue;

            int distance = cal_manhattan_distance(points, cur, i, dp);
            if(distance < min_costs[i]) {
                min_costs[i] = distance;
            }
            if(min_costs[i] < cur_min) {
                cur_min = min_costs[i];
                next = i;
            }
        }

        if(cur_min == INT32_MAX) cur_min = 0;
        printf("%d\n", cur_min);

        result += cur_min;
        cur = next; // if -1, exit while loop
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int points_col_len = 2;

    int **points = malloc(POINT_LEN*sizeof(int));
    for(int i=0;i<POINT_LEN;i++) {
        points[i] = malloc(2*sizeof(int));
        memcpy(points[i], &test_points[i][0], 2*sizeof(int));
    }

    printf("result: %d\n", minCostConnectPoints(points, POINT_LEN, &points_col_len));




}

