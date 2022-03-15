#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
*/


char test_str[] = "lee(t(c)o)de)";
// char test_str[] = "a)b(c)d";
// char test_str[] = "))((";
// char test_str[] = "(fefkm()ffe)";

char *minRemoveToMakeValid(char *s) {
    int length = strlen(s);

    int cnt1 = 0;
    int cnt2 = 0;
    for(int i=0;i<length;i++) {
        if(s[i] == '(') {
            cnt1++;
        }
        else if(s[i] == ')') {
            if(cnt1 == 0) {
                s[i] = '.';
            }
            else {
                cnt1--; // stack pop
            }
        }

        if(s[length-1-i] == ')') {
            cnt2++;
        }
        else if(s[length-1-i] == '(') {
            if(cnt2 == 0) {
                s[length-1-i] = '.';
            }
            else {
                cnt2--;
            }
        }
    }

    // printf("=> %s\n", s); 
    // remove '.'
    int i_temp = 0;
    for(int i=0;i<length;i++) {
        if(s[i] != '.') {
            s[i_temp++] = s[i];
        }
    }
    if(i_temp < length) s[i_temp] = '\0';

    return s;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    char *result = minRemoveToMakeValid(test_str);
    printf("%s\n", result);

}

