#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_n = 5;

/*
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
*/


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *countBits(int n, int *returnSize){
    int *result = malloc(sizeof(int)*(n+1));
    memset(result, 0, sizeof(int)*(n+1));

    *returnSize = n + 1;

    for(int i=0;i<=n;i++) {
        int temp = 0;
        for(int k=0;k<32;k++) {
            if(i & (1<<k)) temp++;
        }
        result[i] = temp;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int reture_size;
    int *array = countBits(test_n, &reture_size);
    for(int i=0;i<reture_size;i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");


}

