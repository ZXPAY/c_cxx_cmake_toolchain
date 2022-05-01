#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_s[] = "ab#c";
char test_t[] = "ad#c";

int trim_backspace(char *s, int len) {
    int i_s = 0;
    for(int i=0;i<len;i++) {
        if(s[i] == '#') {
            i_s--;
            if(i_s < 0) i_s = 0;
        }
        else {
            s[i_s++] = s[i];
        }
    }
    s[i_s] = '\0';

    return i_s;
}

bool backspaceCompare(char *s, char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    int count_s = trim_backspace(&s, len_s);
    int count_t = trim_backspace(&t, len_t);

    printf("%s, %s\n", s, t);

    if(count_s != count_t) return false;

    for(int i=0;i<count_s;i++) {
        if(s[i] != t[i]) return false;
    }

    return true;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", backspaceCompare(test_s, test_t));

    return 0;
}

