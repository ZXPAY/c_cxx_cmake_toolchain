#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int TEST_COSTS[4][2] = {{10, 20}, {30, 200}, {400, 50}, {30, 20}};
int TEST_COSTS[8][2] = {{515,563},{451,713},{537,709},{343,819},{855,779},{457,60},{650,359},{631,42}};
#define COST_LEN (sizeof(TEST_COSTS) / sizeof(int) / 2)


/*
A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person to city b is bCosti.

Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.
*/

int cmp(int *a, int *b) {
    return *a - *b;
}

int twoCitySchedCost(int **costs, int costsSize, int *costsColSize) {
    assert(!(costsSize&1));

    int result = 0;
    int *d_ab = malloc(costsSize*sizeof(int));
    for(int i=0;i<costsSize;i++) {
        d_ab[i] = costs[i][0] - costs[i][1]; // negative: a good, positive: b good
        result += costs[i][0];  // Send all people to a
    }

    // printf("===== sorting =====\n");
    qsort(d_ab, costsSize, sizeof(int), cmp);
    // for(int i=0;i<costsSize;i++) {
    //     printf("%d\n", d_ab[i]);
    // }


    // d_ab = a - b
    // b = a - d_ab
    for(int i=costsSize>>1;i<costsSize;i++) {
        result -= d_ab[i];
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }
    int **test_costs = malloc(COST_LEN*sizeof(int *));
    for(int i=0;i<COST_LEN;i++) {
        test_costs[i] = malloc(2 * sizeof(int));
        memcpy(test_costs[i], &TEST_COSTS[i][0], 2*sizeof(int));
    }

    int col_len = 2;
    printf("result: %d\n", twoCitySchedCost(test_costs, COST_LEN, &col_len));


}

