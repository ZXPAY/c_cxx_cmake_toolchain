#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
Every non-negative integer n has a binary representation.  For example, 5 can be represented as "101" in binary, 11 as "1011" in binary, and so on.  Note that except for n = 0, there are no leading zeroes in any binary representation.

The complement of a binary representation is the number in binary you get when changing every 1 to a 0 and 0 to a 1.  For example, the complement of "101" in binary is "010" in binary.

For a given number n in base-10, return the complement of it's binary representation as a base-10 integer.
*/


int TEST_N = 10;

int bitwiseComplement(int n){
    int NUM, k;
    for(k=30;k>0;k--) {
        if(n & (1 << k)) {
            break;
        }
    }
    NUM = k;
    int mask = 0;
    for(int i=0;i<=NUM;i++) {
        mask |= 1<<i;
    }
    // printf("%d, %x\n", NUM, mask);

    return (~n) & mask;
}

int main() {
    printf("start\n");

    printf("bitwiseComplement: %x\n", bitwiseComplement(TEST_N));

}
