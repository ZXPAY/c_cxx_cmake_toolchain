#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int *test_string[] = {"10","0001","111001","1","0"};
#define LEN 5
#define M 5
#define N 3


typedef struct _mystruct {
    int c_0;
    int c_1;
} one_zero_t;

void count_0_and_1(char *s, one_zero_t *one_zero) {
    for(int i=0;i<strlen(s);i++) {
        if(s[i] == '0') {
            one_zero->c_0++;
        }
        else if(s[i] == '1') {
            one_zero->c_1++;
        }
    }
}


int findMaxForm(char **strs, int strsSize, int m, int n) {
    one_zero_t *ones_zeros = malloc(strsSize*sizeof(one_zero_t));
    memset(ones_zeros, 0, strsSize*sizeof(one_zero_t));
    for(int i=0;i<strsSize;i++) {
        count_0_and_1(strs[i], &ones_zeros[i]);
        printf("%8s: 0: %2d, 1: %2d\n", strs[i], ones_zeros[i].c_0, ones_zeros[i].c_1);
    }

    int **dp = malloc((m+1)*sizeof(int *));
    for(int i=0;i<=m;i++) {
        dp[i] =(int *)malloc((n+1)*sizeof(int));
        memset(dp[i], 0, (n+1)*sizeof(int));
    }

    for(int i=0;i<strsSize;i++) {
        for(int j=m;j>=ones_zeros[i].c_0;j--) {
            for(int k=n;k>=ones_zeros[i].c_1;k--) {
                int temp = 1 + dp[j-ones_zeros[i].c_0][k-ones_zeros[i].c_1];
                if(temp > dp[j][k]) {
                    dp[j][k] = temp;
                }
            }
        }
    }

    for(int i=0;i<=m;i++) {
        for(int j=0;j<=n;j++) {
            printf("%2d,", dp[i][j]);
        }
        printf("\n");
    }

    return dp[m][n];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", findMaxForm(test_string, LEN, M, N));



}

