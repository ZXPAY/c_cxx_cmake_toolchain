#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
We distribute some number of candies, to a row of n = num_people people in the following way:

We then give 1 candy to the first person, 2 candies to the second person, and so on until we give n candies to the last person.

Then, we go back to the start of the row, giving n + 1 candies to the first person, n + 2 candies to the second person, and so on until we give 2 * n candies to the last person.

This process repeats (with us giving one more candy each time, and moving to the start of the row after we reach the end) until we run out of candies.  The last person will receive all of our remaining candies (not necessarily one more than the previous gift).

Return an array (of length num_people and sum candies) that represents the final distribution of candies.
*/


// candies 7, people 4, Answer is [1, 2, 3, 1]
// candies 10, people 3, Answer is [5, 2, 3]

#define CANDIES 60
#define PEOPLES 4


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *distributeCandies(int candies, int num_people, int *returnSize){
    *returnSize = num_people;
    int *result = (int *)malloc(num_people*sizeof(int));
    memset(result, 0, num_people*sizeof(int));

    int give_n = 1;
    int i = 0;
    int residual = candies;

    while(residual > 0) {
        if(give_n > residual) {
            give_n = residual;
            result[i] += give_n;
            return result;
        }
        else {
            result[i++] += give_n;
        }
        residual -= give_n;
        give_n++;
        if(i == num_people) i = 0;
    }

    return result;
}

int main() {
    printf("start\n");

    int return_size;
    int *ans = distributeCandies(CANDIES, PEOPLES, &return_size);
    for(int i=0;i<return_size;i++) {
        printf("%d, ", ans[i]);
    }
    printf("\n");

}
