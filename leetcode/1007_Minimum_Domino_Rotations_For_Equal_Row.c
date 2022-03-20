#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* ans: 2 */
int test_tops[] = {2,1,2,4,2,2};
int test_bottoms[] = {5,2,6,2,2,2};

/* ans: 1 */
// int test_tops[] = {1,2,1,1,1,2,2,2};
// int test_bottoms[] = {2,1,2,2,2,2,2,2};
#define ARRAY_SIZE  (sizeof(test_tops) / sizeof(int))

/*
In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.

If it cannot be done, return -1.
*/


bool is_seen(int *seens, int seen_count, int target) {
    for(int i=0;i<seen_count;i++) {
        if(seens[i] == target) return true;
    }

    return false;
}

int minDominoRotations(int *tops, int topsSize, int *bottoms, int bottomsSize) {
    assert(topsSize == bottomsSize);

    int already_search_n[6] = {0, 0, 0, 0, 0, 0};
    int i_seen = 0;

    int min_count = INT32_MAX;
    for(int i=0;i<topsSize;i++) {
        int all_to_n = tops[i];

        if(is_seen(already_search_n, i_seen, all_to_n)) {
            continue;
        }
        else {
            assert(i_seen<6);
            already_search_n[i_seen++] = all_to_n;
        }

        int count = 0;
        for(int j=0;j<topsSize;j++) {
            if((tops[j] != all_to_n) && (bottoms[j] == all_to_n)) {
                count++;
            }
            else if((tops[j] != all_to_n) && (bottoms[j] != all_to_n)) {
                break;
            }

            if((j == topsSize-1) && (min_count > count)) {
                min_count = count;
            }

            // printf("%d,%d, [%d]: %d\n", tops[j], bottoms[j], all_to_n, count);
        }
    }

    i_seen = 0;
    for(int i=0;i<bottomsSize;i++) {
        int all_to_n = bottoms[i];

        if(is_seen(already_search_n, i_seen, all_to_n)) {
            continue;
        }
        else {
            assert(i_seen<6);
            already_search_n[i_seen++] = all_to_n;
        }

        int count = 0;
        for(int j=0;j<bottomsSize;j++) {
            if((bottoms[j] != all_to_n) && (tops[j] == all_to_n)) {
                count++;
            }
            else if((bottoms[j] != all_to_n) && (tops[j] != all_to_n)) {
                break;
            }

            if((j == bottomsSize-1) && (min_count > count)) {
                min_count = count;
            }

            // printf("%d,%d, [%d]: %d\n", tops[j], bottoms[j], all_to_n, count);
        }
    }    

    if(min_count == INT32_MAX) return -1;

    return min_count;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("min count: %d\n", minDominoRotations(test_tops, ARRAY_SIZE, test_bottoms, ARRAY_SIZE));



}

