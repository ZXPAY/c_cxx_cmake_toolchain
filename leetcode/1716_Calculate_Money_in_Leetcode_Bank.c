#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.

He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday.
Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.
*/


static int test_input[] = {
    4, 10, 20
};


static int test_output[] = {
    10, 37, 96
};

int totalMoney(int n) {
    int base_mon = 0;
    int temp_sum = 0;
    int sum = 0;
    
    for(int i=0;i<n;i++) {
        if(i%7 == 0) {
            // printf("============\n");
            base_mon++;
            temp_sum = base_mon;
        }
        // printf("%d\n", temp_sum);
        sum += temp_sum;
        temp_sum ++;
    }

    return sum;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
        // printf("arg[%d]: %s\n", i, argv[i]);
    // }
    uint32_t test_int = 0;
    if(argc == 2) {
        sscanf(argv[1], "%d", &test_int);
        if(test_int >= 3) test_int = 0;
    }

    printf("test input: %d\n", test_input[test_int]);
    printf("test output: %d\n", test_output[test_int]);
    
    if(totalMoney(test_input[test_int]) == test_output[test_int]) {
        printf("Test success\n");
    }
    else {
        printf("Test fail\n");
    }

}

