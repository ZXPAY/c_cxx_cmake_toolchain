#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char *test_string_list[] = {
    "aabbccdde","e"
};

#define LIST_LENGTH (sizeof(test_string_list) / sizeof(test_string_list[0]))

bool makeEqual(char **words, int wordsSize) {
    int *count_map = malloc(26*sizeof(int));
    memset(count_map, 0, 26*sizeof(int));

    for(int i=0;i<wordsSize;i++) {
        for(int j=0;j<strlen(words[i]);j++) {
            count_map[words[i][j]-'a']++;
        }
    }

    for(int i=0;i<26;i++) {
        if(count_map[i] != 0) {
            if(count_map[i] % wordsSize) return false;
            printf("[%c]: %d\n", i+'a', count_map[i]);
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", makeEqual(test_string_list, LIST_LENGTH));


}

