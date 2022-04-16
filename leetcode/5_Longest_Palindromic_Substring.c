#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "fqwabawq";    // odd, length = 7
char test_string[] = "abccbaccw";   // even, length = 6
// char test_string[] = "bbbb";   // even, length = 4

char *longestPalindrome(char *s) {
    int length = strlen(s);
    char *result = malloc((length+1)*sizeof(char));
    memset(result, 0, (length+1)*sizeof(char));
    int result_len = 0;

    for(int i=0;i<length;i++) {
        int i_left = i;
        int i_right = i;
        int temp = 0;
        
        // Odd length
        while(i_left >= 0 && i_right < length && s[i_left] == s[i_right]) {
            temp = i_right - i_left + 1;
            printf("o: %d\n", i_right-i_left+1);
            if(temp > result_len) {
                memcpy(result, &s[i_left], temp*sizeof(char));
                result_len = temp;
            }
            i_left--;
            i_right++;
        }

        // Even length
        i_left = i;
        i_right = i+1;
        temp = 0;
        while(i_left >= 0 && i_right < length && s[i_left] == s[i_right]) {
            temp = i_right - i_left + 1;
            printf("e: %d\n", i_right-i_left+1);
            if(temp > result_len) {
                memcpy(result, &s[i_left], temp*sizeof(char));
                result_len = temp;
            }
            i_left--;
            i_right++;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }



    printf("result: %s\n", longestPalindrome(test_string));


}

