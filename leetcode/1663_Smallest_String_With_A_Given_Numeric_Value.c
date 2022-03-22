#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* "aay" */
// #define TEST_N  3
// #define TEST_K  27


/* "aaszz" */
// #define TEST_N  5
// #define TEST_K  73


/* "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz" */
#define TEST_N  90
#define TEST_K  1191

/*
The numeric value of a lowercase character is defined as its position (1-indexed) in the alphabet, so the numeric value of a is 1, the numeric value of b is 2, the numeric value of c is 3, and so on.

The numeric value of a string consisting of lowercase characters is defined as the sum of its characters' numeric values. For example, the numeric value of the string "abe" is equal to 1 + 2 + 5 = 8.

You are given two integers n and k. Return the lexicographically smallest string with length equal to n and numeric value equal to k.

Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.
*/



/* Greedy algorithm */
char *getSmallestString(int n, int k) {
    int residual = k;

    // 1. put 'a' first
    // 2. total is n
    char *result = malloc((n+1) * sizeof(char));
    memset(result, 0, (n+1)*sizeof(char));

    for(int i=0;i<n-1;i++) {
        result[i] = 1;
        residual--;
    }

    int index = n-1;
    while(residual > 0) {
        printf("%d\n", residual);
        assert(index>=0);
        
        int temp_sum = residual + result[index];
        if(temp_sum <= 26) {
            result[index] += residual;
            residual = 0;
        }
        else if(temp_sum > 26) {
            int temp = 26 - result[index];
            result[index] = 26;
            residual -= temp;
            index--;
        }
    }

    for(int i=0;i<n;i++) {
        result[i] += 'a' - 1;
    }

    return result;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    /* print the table */
    
    for(int i=0;i<26;i++) {
        printf("[%2c]: %2d, ", 'a'+i, i+1);
        if(i&1) printf("\n");
    }


    char *result = getSmallestString(TEST_N, TEST_K);
    printf("result: %s\n", result);
}

