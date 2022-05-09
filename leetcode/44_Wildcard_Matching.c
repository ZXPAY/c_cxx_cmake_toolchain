#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_s[] = "aabbbmrekaoc";
char test_p[] = "a?b*a?c";

bool help(char *s, int s_len, char *p, int p_len, int i_s, int i_p) {
    if(i_s == s_len && i_p == p_len) return true;
    else if(i_s == s_len) return false;

    if(p[i_p] == '*') {
        if(i_p < p_len) return true;
        if(p[i_p+1] == s[i_s]) {
            /* Try to search next */
            return help(s, s_len, p, p_len, i_s+1, i_p);
        }
        else {
            return help(s, s_len, p, p_len, i_s+1, i_p);
        }
    }
    else if(i_p < p_len && s[i_s] == p[i_p] || p[i_p] == '?') {
        return help(s, s_len, p, p_len, i_s+1, i_p+1);
    }
    else {
        return false;
    }

}

bool isMatch(char *s, char *p) {
    int len_s = strlen(s);
    int len_p = strlen(p);

    if(len_p > len_s) return false;

    /* p feed s */
    int i_s = 0;
    int i_p = 0;
    while(i_s < len_s) {
        char ch_p = p[i_p++];
        if(i_p == len_p) return false;
        if(ch_p == s[i_s] || ch_p == '?') {
            i_s++;
            continue;
        }
        else if(ch_p == '*') {
            if(i_p < len_p) {
                /* Not the end character */
                while(s[i_s++] != p[i_p]) {
                    if(i_s == len_s) return false;
                }
            }
            else {
                return true;
            }
        }
        else {
            /* Character is different */
            return false;
        }
    }

    return i_s == i_p ? true : false;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", isMatch(test_s, test_p));
}

