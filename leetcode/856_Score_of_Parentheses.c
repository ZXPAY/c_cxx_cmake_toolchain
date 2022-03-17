#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "(((())))()()";
char test_string[] = "(()(()))";



int scoreOfParentheses(char *s) {
    int length = strlen(s);
    int count = 0;
    int counts = 0;
    for(int i=0;i<length;i++) {
        if(s[i] == '(') {
            if(count == 0) count = 1;
            else count *= 2;

        }
        else if(s[i] == ')') {
            counts += count;
            count = 0;
        }
    }

    return counts;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%d\n", scoreOfParentheses(test_string));

}

