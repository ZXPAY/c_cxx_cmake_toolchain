#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "abcabcbb";  // 3
// char test_string[] = "bbbbb";    // 1
// char test_string[] = "pwwkew";    // 3
char test_string[] = "dvdf";    // 3
// char test_string[] = "wobgrovw";    // 6

int lengthOfLongestSubstring(char *s) {
    if(s == NULL) return 0;
    int length = strlen(s);
    if(length == 0) return 0;

    int left = 0;
    int max_count = 0;
    int *map = malloc(sizeof(int)*256);
    memset(map, 0xFF, sizeof(int)*256);
    map[(int)s[0]] = 0;
    for(int i=0;i<length;i++) {
        char r = s[i];
        int index = map[(int)r];
        if (index != -1 && index >= left && index < i) {
            left = index + 1;
        }
        int temp = i - left + 1;
        if(max_count < temp) max_count = temp;

        map[(int)r] = i;
    }

    return max_count;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", lengthOfLongestSubstring(test_string));

}

