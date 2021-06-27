#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
Given numBottles full water bottles, you can exchange numExchange empty water bottles for one full water bottle.

The operation of drinking a full water bottle turns it into an empty bottle.

Return the maximum number of water bottles you can drink.
*/

// output 19
int test_num = 15;
int test_exchange = 4;

void recur_bottle(int numBottles, int numExchange, int residual, int *drink_n) {
    *drink_n += numBottles;
    int res;      // residual
    int exchange; // exchange
    // printf("%d, %d\n", numBottles, residual);
    if(numBottles > 0) {
        exchange = (numBottles+residual) / numExchange;
        res = (numBottles+residual) % numExchange;
        recur_bottle(exchange, numExchange, res, drink_n);
    }
}

int numWaterBottles(int numBottles, int numExchange){
    int drink_bottom = 0;
    int residual = 0;
    recur_bottle(numBottles, numExchange, residual, &drink_bottom);
    return drink_bottom;
}

int main() {
    printf("start\n");

    printf("numWaterBottles: %d\n", numWaterBottles(test_num, test_exchange));

}
