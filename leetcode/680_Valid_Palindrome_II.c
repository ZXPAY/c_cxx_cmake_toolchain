#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


// char test_str[] = "aba";
char test_str[] = "abc";

/*
Given a string s, return true if the s can be palindrome after deleting at most one character from it.
*/

#define ERROR_COUNT 1

bool validPalindrome_help(char *s, int i_left, int i_right, int *er_count) {
    if(i_left > i_right) return true;

    if(s[i_left] != s[i_right]) {
        (*er_count)++;
        if(*er_count > ERROR_COUNT) {
            return false;
        }
        else {
            bool left_route = validPalindrome_help(s, i_left+1, i_right, er_count);
            bool right_route = validPalindrome_help(s, i_left, i_right-1, er_count);
            if(left_route == false && right_route == false) return false;
        }
    }
    else {
        return validPalindrome_help(s, i_left+1, i_right-1, er_count);
    }
    return true;
}

bool validPalindrome(char *s) {
    int length = strlen(s);
    if(length < 2) return false;

    int i_left = 0;
    int i_right = length -1;
    int er_count = 0;

    return validPalindrome_help(s, i_left, i_right, &er_count);
}

int main(int argc, char *argv[]) {

    printf("validPalindrome: %d\n", validPalindrome(test_str));


}

