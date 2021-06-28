#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
Balanced strings are those that have an equal quantity of 'L' and 'R' characters.

Given a balanced string s, split it in the maximum amount of balanced strings.

Return the maximum amount of split balanced strings.
*/

char test_str[] = "RLRRRLLRLL";
// answer is 3 RL, RRLL, RL, RL


#define FLAG_R 'R'
#define FLAG_L 'L'

int balancedStringSplit(char *s){
    int str_len = strlen(s);
    if(str_len == 0) return 0;

    int r_cnt = 0;
    int l_cnt = 0;
    int result = 0;

    for(int i=0;i<str_len;i++) {
        switch (s[i]) {
            case 'R':
                r_cnt++;
                break;
            case 'L':
                l_cnt++;
                break;
        }
        if((r_cnt == l_cnt) && (r_cnt != 0) && (l_cnt != 0)) {
            result++;
        }
    }
    return result;
}

int main() {
    printf("start\n");

    printf("balancedStringSplit: %d\n", balancedStringSplit(test_str));

}
