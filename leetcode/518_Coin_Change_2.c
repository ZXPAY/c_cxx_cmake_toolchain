#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_coins[] = {1, 2, 5};
#define COIN_SIZE (sizeof(test_coins) / sizeof(int))
#define TEST_AMOUNT 5

int change(int amount, int *coins, int coinsSize) {
    int *dp = (int *)malloc((amount+1)*sizeof(int));
    memset(dp, 0, (amount+1)*sizeof(int));
    dp[0] = 1;

    for(int i=0;i<coinsSize;i++) {
        for(int j=coins[i];j<=amount;j++) {
            dp[j] += dp[j-coins[i]];
        }
    }

    for(int i=0;i<=amount;i++) {
        printf("%d,", dp[i]);
    }
    printf("\n");

    return dp[amount];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", change(TEST_AMOUNT, test_coins, COIN_SIZE));

}

