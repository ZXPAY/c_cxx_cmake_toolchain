#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_string[] = "abb";

int removePalindromeSub(char *s) {
    int j = strlen(s) - 1;
    int i = 0;

    while(j > i) {
        if(s[i] != s[j]) return 2;
        i++;
        j--;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", removePalindromeSub(test_string));



}

