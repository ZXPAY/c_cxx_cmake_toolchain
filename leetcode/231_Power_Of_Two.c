#include <stdio.h>
#include <stdbool.h>

#define TEST_N  16

bool isPowerOfTwo(int n) {
    if(n < 0) {
        return 0;
    }
    int bit_sum = 0;
    for(int i=0;i<32;i++) {
        bit_sum += (n & 1);
        n >>= 1;
    }
    if(bit_sum == 1) {
        return true;
    }
    return false;
}

int main() {
    printf("start\n");

    printf("test %d is power of two: %d\n", TEST_N, isPowerOfTwo(TEST_N));

}
