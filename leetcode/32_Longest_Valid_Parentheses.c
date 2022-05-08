#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define TEST_LEN 5
char *test_string[] = {
    "(()",
    ")()()",
    "",
    "()()())((((()))))",
    "()(()"
};


int longestValidParentheses(char *s) {
    int length = strlen(s);
    int *buf = (int *)malloc((length+1)*sizeof(int));
    int i_buf = 0;

    int max_count = 0;
    buf[i_buf++] = -1;
    /* Using stack */
    for(int i=0;i<length;i++) {
        if(s[i] == '(') {
            buf[i_buf++] = i;
        }
        else if(s[i] == ')') {
            i_buf--;
            if(i_buf == 0) {
                buf[i_buf++] = i;
            }
            else {
                int count = i - buf[i_buf-1];
                max_count = max_count < count ? count : max_count;
            }
        }
    }

    return max_count;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    for(int i=0;i<TEST_LEN;i++) {
        printf("result[%d]: %2d\n", i, longestValidParentheses(test_string[i]));
    }
    printf("ans: 2, 4, 0, 10, 2\n");


}

