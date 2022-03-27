#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


int test_mat[5][5] =
    {{1,1,0,0,0},
    {1,1,1,1,0},
    {1,0,0,0,0},
    {1,1,0,0,0},
    {1,1,1,1,1}}; 
#define K  (3)
#define M  (sizeof(test_mat) / sizeof(test_mat[0]))


/*
You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will appear to the left of all the 0's in each row.

A row i is weaker than a row j if one of the following is true:

The number of soldiers in row i is less than the number of soldiers in row j.
Both rows have the same number of soldiers and i < j.
Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
*/


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *kWeakestRows(int **mat, int matSize, int *matColSize, int k, int *returnSize) {
    *returnSize = k;
    for(int i=0;i<matSize;i++) {
        for(int j=1;j<*matColSize;j++) {
            mat[i][0] += mat[i][j];
        }
    }

    // for(int i=0;i<matSize;i++) {
    //     printf("%d\n", mat[i][0]);
    // }
    int *result = malloc(k*sizeof(int));
    int candicate = 0;
    int count = 0;
    int index = 0;
    /* Greedy approach */
    while(count < k) {
        if(mat[index][0] != INT32_MAX) {
            if(mat[index][0] == candicate) {
                result[count++] = index;
                mat[index][0] = INT32_MAX;
            }
        }

        index++;
        if(index == matSize) {
            index = 0;
            candicate++;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **mat = malloc(sizeof(int *)*M);

    for(int i=0;i<M;i++) {
        mat[i] = malloc(sizeof(int)*M);
        memcpy(mat[i], &test_mat[i][0], M*sizeof(int));
    }

    int col_size = M;
    int return_size;
    int *result = kWeakestRows(mat, M, &col_size, K, &return_size);

    printf("result: {");
    for(int i=0;i<return_size;i++) {
        printf("%d, ", result[i]);
    }
    printf("}\n");

}

