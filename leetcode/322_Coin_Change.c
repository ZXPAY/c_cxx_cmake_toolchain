#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_coint[] = {3, 7};
#define COIN_SIZE (sizeof(test_coint) / sizeof(int))
#define TEST_AMOUNT 20


int coinChange(int *coins, int coinsSize, int amount) {
    int *dp = (int *)malloc((amount+1)*sizeof(int));
    for(int i=0;i<=amount;i++) {
        dp[i] = INT32_MAX;
    }
    dp[0] = 0;

    for(int amt=1;amt<=amount;amt++) {
        /* choose one amount, find the minimal coins count */
        int minimal_coin_count = INT32_MAX;
        for(int j=0;j<coinsSize;j++) {
            if(amt >= coins[j]) {
                if(minimal_coin_count > dp[amt - coins[j]]) {
                    minimal_coin_count = dp[amt-coins[j]];
                }
            }
        }
        if(minimal_coin_count != INT32_MAX) {
            dp[amt] = minimal_coin_count + 1;
            printf("coin $%d, usage count: %d\n", amt, dp[amt]);
        }
        else {
            printf("coin $%d, fail to choose coins\n", amt);
        }
    }

    return dp[amount] == INT32_MAX ? -1 : dp[amount];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", coinChange(test_coint, COIN_SIZE, TEST_AMOUNT));



}

