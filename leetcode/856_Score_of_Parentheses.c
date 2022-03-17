#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "(((())))()()";  // 10
char test_string[] = "(()(()))";      // 6

int scoreOfParentheses(char *s) {
    int length = strlen(s);

    int *buf = malloc(sizeof(int)*(length/2));
    memset(buf, 0, sizeof(int)*(length/2));
    int i_buf = 0;
    int count = 0;
    
    for(int i=0;i<length;i++) {
        if(s[i] == '(') {
            buf[i_buf++] = count;
            count = 0;
        }
        else if(s[i] == ')') {
            assert(i_buf>0);
            if(count == 0) {
                count = buf[i_buf-1] + 1;
            }
            else {
                count = buf[i_buf-1] + 2 * count;
            }
            i_buf--;
        }
        // printf("= %d\n", count);
    }

    return count;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("%d\n", scoreOfParentheses(test_string));

}

