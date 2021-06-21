#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
There is a biker going on a road trip. The road trip consists of n + 1 points at different altitudes.
The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n where gain[i] is the net gain in altitude between points i​​​​​​ and i + 1 for all (0 <= i < n). 
Return the highest altitude of a point.
*/

// int test_gain[] = {-5, 1, 5, 0, -7};  // answer 1
int test_gain[] = {-4,-3,-2,-1,4,3,2};  // answer 0


int largestAltitude(int *gain, int gainSize){
    int temp_max = 0;
    int last_gain;
    for(int i=0;i<gainSize+1;i++) {
        if(i == 0) {
            last_gain = 0;
        }
        else {
            last_gain += gain[i-1];
            if(last_gain > temp_max) {
                temp_max = last_gain;
            }
        }
    }

    return temp_max;
}


int main(void) {
    printf("start \n");

    int gain_sz = sizeof(test_gain) / sizeof(int);
    printf("gain size: %d\n", gain_sz);

    int *altitude = (int *)malloc((gain_sz+1)*sizeof(int));

    printf("Altitude: ");
    for(int i=0;i<gain_sz+1;i++) {
        if(i == 0) {
            altitude[i] = 0;
        }
        else {
            altitude[i] = altitude[i-1] + test_gain[i-1];
        }
        printf("%d, ", altitude[i]);
    }
    printf("\n");

    printf("largest altitude: %d\n", largestAltitude(test_gain, gain_sz));

    free(altitude);
    return 0;
}

