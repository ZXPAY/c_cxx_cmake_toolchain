#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.
*/


// int piles[] = {3, 6, 7, 8};
int piles[] = {30,11,23,4,20};

#define ARRAY_SIZE  (sizeof(piles) / (sizeof(int)))
#define H           6


int consume_hours(int *pile, int length, int k) {
    int i = 0;
    int h = 0;
    while(true) {
        int bananas = pile[i];
        // be carefule about the rounding in integers
        if (bananas % k == 0)
            h += bananas/k;
        else
            h += (bananas/k + 1);

        i++;
        if (i >= length) break;
    }

    return h;
}


int min_eating_speed_help(int *piles, int pile_len, int h, int k_start, int k_end) {
    int result = -1;
    int k_mid = (k_start + k_end) / 2;

    int consume_h = consume_hours(piles, pile_len, k_mid);
    // printf("consume hours: %d, %d, {%d, %d}\n", k_mid, consume_h, k_start, k_end);

    if(consume_h <= h) {
        result = k_mid;
        // go left
        if(k_start < k_mid) {
            int temp = min_eating_speed_help(piles, pile_len, h, k_start, k_mid-1);
            if(temp != -1) {
                result = temp;
            }
        }
    }
    else {
        // go right
        if(k_end > k_mid) {
            int temp = min_eating_speed_help(piles, pile_len, h, k_mid+1, k_end);
            if(temp != -1) {
                result = temp;
            }
        }
    }
    

    return result;
}

int minEatingSpeed(int *piles, int pilesSize, int h) {
    return min_eating_speed_help(piles, pilesSize, h, 1, 1000000000);
}

int main(int argc, char *argv[]) {
    printf("%d\n", minEatingSpeed(piles, ARRAY_SIZE, H));

    // printf("%d\n", consume_hours(piles, ARRAY_SIZE, 50));
}

