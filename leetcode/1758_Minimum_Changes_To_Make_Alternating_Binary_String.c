#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.
*/

char test_string[] = "1010";

int minOperations(char *s) {
    int char_len = strlen(s);
    if(char_len == 0) return 0;
    
    int cnt_0 = 0;
    int cnt_1 = 0;
    char temp_ch0 = '0';
    char temp_ch1 = '1';

    if(temp_ch0 != s[0]) {
        cnt_0++;
    }
    if(temp_ch1 != s[0]) {
        cnt_1++;
    }

    for(int i=1;i<char_len;i++) {
        if(temp_ch0 == s[i]) {
            cnt_0++;
        }
        if(temp_ch1 == s[i]) {
            cnt_1++;
        }
        if('0' == temp_ch0) temp_ch0 = '1';
        else temp_ch0 = '0';
        if('0' == temp_ch1) temp_ch1 = '1';
        else temp_ch1 = '0';
    }
    

    if(cnt_0 < cnt_1) return cnt_0;
    return cnt_1;
}

int main() {
    printf("start\n");

    printf("minOperations: %d\n", minOperations(test_string));

}
