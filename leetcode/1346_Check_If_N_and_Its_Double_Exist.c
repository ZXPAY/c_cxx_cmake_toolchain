#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Given an array arr of integers, check if there exists two integers N and M 
such that N is the double of M ( i.e. N = 2 * M).

More formally check if there exists two indices i and j such that :

i != j
0 <= i, j < arr.length
arr[i] == 2 * arr[j]
 
*/

int test_array[] = {0, 0};

bool checkIfExist(int *arr, int arrSize) {
    int temp;
    for(int i=0;i<arrSize;i++) {
        temp = arr[i]*2;
        for(int j=0;j<arrSize;j++) {
            // printf("%d, %d\n", temp, arr[j]);
            if(temp == arr[j] && i != j) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    printf("start\n");

    printf("checkIfExist: %d\n", checkIfExist(test_array, sizeof(test_array)/sizeof(int)));

}
