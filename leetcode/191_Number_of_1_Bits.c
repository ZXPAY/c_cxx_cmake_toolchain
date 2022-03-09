#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// #define TEST_N 0x0000000b
// #define TEST_N 0x0010000b
#define TEST_N 0b11111111111111111111111111111101

int hammingWeight(uint32_t n) {
    int cnt = 0;
    for(int i=0;i<32-__builtin_clz(n);i++) if(n & (1<<i)) cnt++;
    return cnt;
}

int main(int argc, char *argv[]) {
    printf("%d\n", hammingWeight(TEST_N));
}

