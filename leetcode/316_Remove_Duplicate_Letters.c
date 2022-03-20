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
    int *char_last_index = malloc(26*sizeof(int));
    memset(char_last_index, 0, 26*sizeof(int));

    bool *seen = malloc(26*sizeof(bool));
    memset(seen, false, 26*sizeof(bool));

    int *buf = malloc(length*sizeof(int));
    memset(buf, 0, length*sizeof(int));    
    int i_buf = 0;

    for(int i=0;i<length;i++) {
        char_last_index[s[i]-'a'] = i;
    }

    for(int i=0;i<length;i++) {
        int curr = s[i] - 'a';
        if(seen[curr]) continue;
        while(true) {
            bool flag = false;
            if(i_buf > 0) {
                if(buf[i_buf-1] > s[i]) {
                    if(i < char_last_index[buf[i_buf-1]-'a']) {
                        flag = true;
                    }
                }
            }
            if(false == flag) break;
            seen[buf[i_buf-1]-'a'] = false;
            i_buf--;
        }
        buf[i_buf++] = s[i];
        seen[curr] = true;

    }

    for(int i=0;i<i_buf;i++) {
        s[i] = buf[i];
    }

    if(i_buf < length)
        s[i_buf] = '\0';


    free(char_last_index);
    free(buf);
    free(seen);

    return s;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    char *string_after = removeDuplicateLetters(test_string);
    printf("result: %s\n", string_after);


}

