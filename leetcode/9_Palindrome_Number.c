#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define TEST_N 12231

bool isPalindrome(int x) {
    if(x < 0) return false;

    char *test = malloc(32*sizeof(char));
    memset(test, 0, 32*sizeof(char));

    int j = 0;
    while(x) {
        test[j++] = (x%10) + '0';
        x /= 10;
    }
    int i = 0;
    j--;
    while(j > i) {
        if(test[i] != test[j]) return false;
        j--;
        i++;
    }

    return true;
}

bool isPalindrome2(int x) {
    if(x < 0) return false;
    long temp_x = x;
    long reverse_num = 0;
    while(temp_x) {
        reverse_num *= 10L;
        reverse_num += temp_x%10;
        temp_x /= 10L;
    }

    return x == reverse_num;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result %d\n", isPalindrome(TEST_N));
    printf("result %d\n", isPalindrome2(TEST_N));
}

