#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* ans: 2 */
// int test_people[] = {1, 2};
// int test_limit = 3;

/* ans: 3 */
// int test_people[] = {3, 2, 2, 1};
// int test_limit = 3;

/* ans: 4 */
// int test_people[] = {3, 5, 3, 4};
// int test_limit = 5;

/* ans: 3 */
int test_people[] = {21,40,16,24,30};
int test_limit = 50;

#define PEOPLE_SIZE sizeof(test_people) / sizeof(int)

/*
You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.
*/

int cmp(int *a, int *b) {
    return *a - *b;
}

int numRescueBoats(int *people, int peopleSize, int limit) {
    int result = 0;
    // Sorting
    qsort(people, peopleSize, sizeof(int), cmp);

    for(int i=0;i<peopleSize;i++) {
        printf("%d\n", people[i]);
    }

    int i = 0;                // from low weight
    int j = peopleSize - 1;   // from high weight

    while(true) {
        // printf("%d, %d\n", i, j);
        result++;
        if(people[i] + people[j] <= limit) {
            i++;
        }
        j--;
        if(i > j) break;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", numRescueBoats(test_people, PEOPLE_SIZE, test_limit));


}

