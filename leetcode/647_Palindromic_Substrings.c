#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


char test_string[] = "aaa";

int countSubstrings(char *s) {
    int result = 0;
    int length = strlen(s);

    for(int i=0;i<length;i++) {
        int i_left = i;
        int i_right = i;

        // Odd length
        while(i_left >= 0 && i_right < length && s[i_left] == s[i_right]) {
            i_left--;
            i_right++;
            result++;
        }

        // Even length
        i_left = i;
        i_right = i+1;
        while(i_left >= 0 && i_right < length && s[i_left] == s[i_right]) {
            i_left--;
            i_right++;
            result++;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", countSubstrings(test_string));
}

