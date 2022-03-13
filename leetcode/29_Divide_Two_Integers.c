#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef int int32_t;

// 2147483647
// int test_dividend = -2147483648;
// int test_divisor = -1;

// 3
// int test_dividend = 10;
// int test_divisor = 3;

// int test_dividend = 7;
// int test_divisor = -3;

// ans: -1073741824
int test_dividend = -2147483648;
int test_divisor = 2;

// ans: -17
// int test_dividend = -2147483648;
// int test_divisor = 122481295;

// ans: 715827882
// int test_dividend = 2147483647;
// int test_divisor = 3;


/*
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.
*/

int divide(int dividend, int divisor) {
    if(dividend == INT32_MIN && divisor == 1) return INT32_MIN;
    if(dividend == INT32_MIN && divisor == -1) return INT32_MAX;
    if(dividend == INT32_MAX && divisor == 1) return INT32_MAX;
    if(dividend == INT32_MAX && divisor == -1) return INT32_MIN;
    if(dividend == INT32_MAX && divisor == INT32_MAX) return 1;
    if(dividend == INT32_MIN && divisor == INT32_MIN) return 1;

    uint8_t sign_bit = !((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0));


    // dividend
    uint32_t N = (uint32_t) dividend;
    if(dividend < 0) N = (~N)+1;
    // divisor
    uint32_t D = (uint32_t) divisor;
    if(divisor < 0) D = (~D)+1;

    // quotient
    uint32_t Q = 0;
    // reminder
    uint32_t R = 0;
    
    // Using long division algorithm
    for(int i=31;i>=0;i--) {
        R <<= 1;
        R |= (N & (1UL<<i))>>i;
        if(R >= D) {
            R = R - D;
            Q |= (1<<i);
        }
    }
    printf("%d, %d\n", Q, R);

    if(sign_bit) {
        return (int32_t) (~Q)+1;
    }
    else if(sign_bit && Q < INT32_MIN) return INT32_MAX;
    else if(Q > INT32_MAX) return INT32_MAX;

    return Q;
}


int main(int argc, char *argv[]) {
    printf("%d\n", divide(test_dividend, test_divisor));
}

