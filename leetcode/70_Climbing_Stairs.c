#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#define TEST_N 10

// 1 -> 1
// 2 -> 2
// 3 -> 3
// 4 -> 5

// Fibonacci
//  f[n] = f[n-1] + f[n-2]


int climbStairs(int n){
    if(n == 1) return n;
    else if(n == 2) return 2;

    int temp[2] = {1, 2};
    int ans = 0;
    for(int i=2;i<n;i++) {
        ans = temp[0] + temp[1];
        // printf("%d, %d, %d\n", temp[0], temp[1], ans);
        temp[0] = temp[1];
        temp[1] = ans;
    }

    return ans;
}


int main() {
    printf("start\n");

    printf("climb %d, steps: %d\n", TEST_N, climbStairs(TEST_N));
}
