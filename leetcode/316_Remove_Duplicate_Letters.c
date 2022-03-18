#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "bcabc"; // abc
char test_string[] = "cbacdcbc"; // acdb


char *removeDuplicateLetters(char *s) {
    int length = strlen(s);
    int *char_count_map = malloc(26*sizeof(int));
    memset(char_count_map, 0, 26*sizeof(int));

    for(int i=0;i<length;i++) {
        assert((s[i]-'a') < 26);
        char_count_map[s[i]-'a']++;
    }
    int i_s = 0;
    for(int i=0;i<length;i++) {
        printf("[%c, %d]: %d\n", i+'a', i+'a', char_count_map[i]);
        // if(char_count_map[i] != 0) s[i_s++] = (char)i+'a';
        char_count_map[s[i]-'a']--;

        // printf("%c, %d\n", s[i], char_count_map[s[i]-'a']);
    }
    printf("i_s: %d\n", i_s);
    s[i_s] = '\0';

    return s;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    char *string_after = removeDuplicateLetters(test_string);
    printf("result: %s\n", string_after);


}

