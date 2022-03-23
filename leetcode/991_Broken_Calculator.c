#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define TEST_VALUE  5
#define TEST_TARGET 8

/*
There is a broken calculator that has the integer startValue on its display initially. In one operation, you can:

multiply the number on display by 2, or
subtract 1 from the number on display.
Given two integers startValue and target, return the minimum number of operations needed to display target on the calculator.
*/


int brokenCalc(int startValue, int target) {
    if(startValue == target) return 0;
    int count = 0;
    // Let target to startValue
    while(true) {
        printf("=> %d\n", target);
        if(target & 1 || ((target+1) == startValue)) { // odd
            target++;
        }
        else if(target < startValue) {
            count += (startValue - target);
            break;
        }
        else {
            target >>= 1;
        }
        count++;
        if(target == startValue) {
            return count;
        }
        assert(count < 10000);
    }
    return count;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%d\n", brokenCalc(TEST_VALUE, TEST_TARGET));


}

