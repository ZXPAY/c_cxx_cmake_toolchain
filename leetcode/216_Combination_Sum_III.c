#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
*/


/* Result: [[1,2,4]] */
#define K1 3
#define N1 7


/* Result: [[1,2,6], [1,3,5], [2,3,4]] */
#define K2 3
#define N2 9

void help(int **result, int *res_count, int *buf, int *i_buf, int *nums, int index, int k, int n) {
    if(*i_buf == k && n == 0) {
        // for(int i=0;i<*i_buf;i++) {
        //     printf("%d,", buf[i]);
        // }
        // printf("\n");

        result[*res_count] = malloc(k*sizeof(int));
        memcpy(result[*res_count], buf, k*sizeof(int));
        (*res_count)++;
        return;
    }

    for(int i=index;i<9;i++) {
        buf[(*i_buf)++] = nums[i];
        help(result, res_count, buf, i_buf, nums, i+1, k, n-nums[i]);
        (*i_buf)--;
    }

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;

    int *nums = malloc(9*sizeof(int));
    for(int i=1;i<=9;i++) nums[i-1] = i;

    int **result = malloc(sizeof(int *)*16);

    int *buf = malloc(10*sizeof(int));
    int i_buf = 0;

    help(result, returnSize, buf, &i_buf, nums, 0, k, n);

    *returnColumnSizes = malloc((*returnSize)*sizeof(int));
    for(int i=0;i<*returnSize;i++) {
        (*returnColumnSizes)[i] = k;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int return_sz;
    int *col_sz;


    int **result1 = combinationSum3(K1, N1, &return_sz, &col_sz);
    printf("result: ");
    for(int i=0;i<return_sz;i++) {
        printf("{");
        for(int j=0;j<col_sz[i];j++) {
            printf("%d,", result1[i][j]);
        }
        printf("}, ");
    }
    printf("\n");


    int **result2 = combinationSum3(K2, N2, &return_sz, &col_sz);
    printf("result: ");
    for(int i=0;i<return_sz;i++) {
        printf("{");
        for(int j=0;j<col_sz[i];j++) {
            printf("%d,", result2[i][j]);
        }
        printf("}, ");
    }
    printf("\n");

}

