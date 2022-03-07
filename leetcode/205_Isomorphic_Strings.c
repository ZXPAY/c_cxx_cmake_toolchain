#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* true */
// char ss[] = "add";
// char tt[] = "egg";

/* false */
// char ss[] = "foo";
// char tt[] = "bar";

/* true */
char ss[] = "paper";
char tt[] = "title";

/* false */
// char ss[] = "babc";
// char tt[] = "baba";

/*
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
*/

bool isIsomorphic(char *s, char *t) {
    int s_len = strlen(s);
    int t_len = strlen(t);

    if(s_len != t_len) return false;

    // a->z
    int *hash_map = (int *)malloc(sizeof(int)*(256));
    memset(hash_map, 0, sizeof(int)*(256));
    int *hash_map_used = (int *)malloc(sizeof(int)*(256));
    memset(hash_map_used, 0, sizeof(int)*(256));

    // Using hash function
    for(int i=0;i<s_len;i++) {
        // printf("=> %d, %d, %c, %c\n", hash_map[(int)s[i]], hash_map_used[(int)t[i]], t[i], s[i]);
        if(hash_map_used[(int)t[i]] != 0) {
            // has already used, check is map ok
            if(hash_map_used[(int)t[i]] != s[i]) return false;
        }
        if(hash_map[(int)s[i]] == 0) {
            hash_map[(int)s[i]] = t[i];
            hash_map_used[(int)t[i]] = s[i];
        }
        else if(hash_map[(int)s[i]] != t[i]) return false;
    }


    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("isIsomorphic: %d\n", isIsomorphic(ss, tt));


}

