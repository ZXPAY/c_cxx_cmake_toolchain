#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Reverse bits of a given 32 bits unsigned integer.

Note:

Note that in some languages such as Java, there is no unsigned integer type. In this case, both input and output will be given as a signed integer type. They should not affect your implementation, as the integer's internal binary representation is the same, whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation. Therefore, in Example 2 above, the input represents the signed integer -3 and the output represents the signed integer -1073741825.
Follow up:

If this function is called many times, how would you optimize it?

*/


#define  TEST_N     43261596   // output 964176192


uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    
    // 32 bit
    for(int i=0;i<32;i++) {
        result |= ((n&(1U<<i)) >> i) << (31-i);
    }
    return result;
}

int main() {
    printf("start\n");

    printf("reverseBits: %d\n", reverseBits(TEST_N));
}
