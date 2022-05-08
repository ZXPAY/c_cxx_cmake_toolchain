#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_string[] = "((()))";


void backtracking(char **result, int *i_result, char *buf, int *i_buf, int n, int left, int right) {
    if(*i_buf == 2*n) {
        // for(int i=0;i<*i_buf;i++) {
        //     printf("%c", buf[i]);
        // }
        // printf("\n");

        memcpy(result[(*i_result)++], buf, 2*n);
        return;
    }
    if(left < n) {
        buf[(*i_buf)++] = '(';
        backtracking(result, i_result, buf, i_buf, n, left+1, right);
        (*i_buf)--;
    }
    if(right < left) {
        buf[(*i_buf)++] = ')';
        backtracking(result, i_result, buf, i_buf, n, left, right+1);
        (*i_buf)--;
    }

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
    char *buf = (char *)malloc((n*2+1)*sizeof(char));
    int i_buf = 0;
    int c = 1;
    for(int i=0;i<n;i++) {
        c *= 4;
    }
    c >>= 1;
    char **result = (char **)malloc(sizeof(char *)*c);
    for(int i=0;i<c;i++) {
        result[i] = (char *)malloc(sizeof(char)*(n*2+1));
        result[i][n*2] = '\0';
    }

    *returnSize = 0;
    backtracking(result, returnSize, buf, &i_buf, n, 0, 0);

    return result;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_sz = 0;
    char **result = generateParenthesis(3, &return_sz);
    printf("{");
    for(int i=0;i<return_sz;i++) {
        printf("%s,", result[i]);
    }
    printf("}\n");

}

