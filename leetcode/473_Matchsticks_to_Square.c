#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int ticks[] = {1,1,2,2,2};  // true
// int ticks[] = {3,3,3,3,4};  // false
// int ticks[] = {5,5,5,5,4,4,4,4,3,3,3,3};  // true
// int ticks[] = {12,12,12,16,20,24,28,32,36,40,44,48,52,56,60};  // false
int ticks[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,102};  // false
#define TICK_SIZE  sizeof(ticks) / sizeof(int)


/*
You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.
*/

int cmp(int *a, int *b) {
    return *b - *a;
}

bool backtracking(int *matchsticks, int length, int *sum, int index, int side_length) {
    // printf("%d\n", index);
    if(index == length) {
        printf("%d, %d, %d, %d\n", sum[0], sum[1], sum[2], sum[3]);
        if( sum[0] == side_length &&
            sum[1] == side_length &&
            sum[2] == side_length &&
            sum[3] == side_length) {
            return true;
        }
        return false;
    }

    for(int i=0;i<4;i++) {
        if(sum[i] + matchsticks[index] <= side_length) {
            sum[i] += matchsticks[index];
            if(backtracking(matchsticks, length, sum, index+1, side_length)) return true;
            sum[i] -= matchsticks[index];
        }
    }
    return false;
}

bool makesquare(int *matchsticks, int matchsticksSize) {
    int sum[4] = {0, 0, 0, 0};
    int temp_sum = 0;
    for(int i=0;i<matchsticksSize;i++) temp_sum += matchsticks[i];
    
    if(temp_sum % 4 != 0) return false;
    
    printf("side length: %d\n", temp_sum>>2);
    
    qsort(matchsticks, matchsticksSize, sizeof(int), cmp);
    return backtracking(matchsticks, matchsticksSize, sum, 0, temp_sum>>2);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("Result: %d\n", makesquare(ticks, TICK_SIZE));
}

