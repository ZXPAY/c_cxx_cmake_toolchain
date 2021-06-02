#include <stdio.h>

#define TEST_N  (234)

int pow_ten(int n) {
    int temp = 1;
    for(int i=0;i<n;i++) {
        temp *= 10;
    }
    return temp;
}

int subtractProductAndSum(int n) {
    int sum_v = 0;
    int mul_v = 1;
    int temp_n = n;
    int temp_digit;
    int temp_pow;

    // parse all digit
    for(int i=0;i<5;i++) {
        temp_pow = pow_ten(i);
        if(temp_n >= temp_pow) {
            temp_digit = (temp_n % (temp_pow*10)) / temp_pow;
            sum_v += temp_digit;
            mul_v *= temp_digit;
            temp_n -= temp_digit * temp_pow;
            printf("%d: %d, %d\n", i, temp_n, temp_digit);
        } 
    }

    return (mul_v - sum_v);
}

int main() {
    printf("start\n");

    printf("subtractProductAndSum: %d\n", subtractProductAndSum(TEST_N));

    return 0;
}

