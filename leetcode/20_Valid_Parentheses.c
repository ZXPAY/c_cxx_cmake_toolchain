#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "()[]{}";
char test_string[] = "([]){";

/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
*/

inline char return_another_bracket(char bracket) {
    switch (bracket) {
        case ')':
            return '(';
        case ']':
            return '[';
        case '}':
            return '{';
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
    }
    return 0;
}

bool isValid(char *s) {
    int length = strlen(s);
    if(length < 2) return false;

    int stack_len = ((length >> 1) + 1);
    char *stack_buf = malloc(sizeof(char)*(stack_len));
    memset(stack_buf, 0, sizeof(char)*stack_len);
    int index = 0;

    bool ok_flag = true;
    for(int i=0;i<length;i++) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
            printf("push: %c\n", s[i]);
            stack_buf[index++] = s[i];
            if(index == stack_len) {
                ok_flag = false;
                break;
            }
        }
        else if(s[i] == ')' || s[i] == ']' || s[i] == '}') {
            index--;
            printf("pop: %d, %c, %c\n", index, stack_buf[index], s[i]);
            if(index < 0) {
                ok_flag = false;
                break;
            }
            else if(stack_buf[index] != return_another_bracket(s[i])) {
                ok_flag = false;
                break;
            }
        }
    }

    free(stack_buf);
    if(index != 0) {
        return false;
    }

    return ok_flag;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("isValid: %d\n", isValid(test_string));


}

