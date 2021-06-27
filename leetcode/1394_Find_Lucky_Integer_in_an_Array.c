#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
Given an array of integers arr, a lucky integer is an integer which has a frequency in the array equal to 
    its value.
Return a lucky integer in the array. If there are multiple lucky integers 
    return the largest of them. If there is no lucky integer return -1.

1 <= arr.length <= 500
1 <= arr[i] <= 500

*/

int test_num[] = {1,2,2,3,3,3};  // answer is 3

#define MAX_LUCKY_NUM 500
int findLucky(int *arr, int arrSize){
    int *hash = (int *)malloc((MAX_LUCKY_NUM+1)*sizeof(int));
    memset(hash, 0, (MAX_LUCKY_NUM+1)*sizeof(int));
    for(int i=0;i<arrSize;i++) hash[arr[i]]++;
    for(int i=MAX_LUCKY_NUM;i>0;i--) {
        if(hash[i] == i) {
			free(hash);
            return i;
        }
    }
	free(hash);
    return -1;
}

int main() {
    printf("start\n");

    printf("findLucky: %d\n", findLucky(test_num, sizeof(test_num) / sizeof(int)));

}
