#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

xor: 1 1 0
     0 0 0
     0 1 1
     1 0 1
*/

void print_binary(int n) {
    for(int i=31;i>=0;i--) {
        if(n&(1<<i)) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");
}


int test_num[] = {3,10,5,25,2,8};  // output: 18

int findMaximumXOR(int *nums, int numsSize){
    int result = 0;
    int mask = 0;

    int *hash = (int *)malloc(numsSize * sizeof(int));
    int hash_cnt = 0;
    int flag = 0;
    int cnt = 0;
    int temp;
    for(int i=30;i>=0;i--) {
        mask |= 1 << i;
        hash_cnt = 0;
        flag = 1;
        for(int j=0;j<numsSize;j++) {
            hash[hash_cnt++] = nums[j] & mask;
            cnt++;
        }

        int candidate = result | (1 << i);
        flag = 0;

        // c = a ^ b => a = c ^ b
        for(int k=0;k<hash_cnt&&flag==0;k++) {
            printf("%x, %x, %x\n", hash[k], candidate, hash[k] ^ candidate);
            temp = hash[k] ^ candidate;
            
            for(int p=0;p<hash_cnt&&flag==0;p++) {
                if(hash[p] == temp) {
                    result = candidate;
                    flag = 1;
                }
            }
        }
    }

    return result;
}

int main() {
    printf("start\n");

    printf("findMaximumXOR: %d\n", findMaximumXOR(test_num, sizeof(test_num)/sizeof(int)));

}
