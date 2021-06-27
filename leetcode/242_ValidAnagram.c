#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
*/

char test_s[] = "anagram";
char test_t[] = "nagaram";

bool isAnagram(char *s, char *t){
    int s_len = strlen(s);
    int t_len = strlen(t);
    if(s_len != t_len || s == NULL || t == NULL) return false;
    int *hash = (int *)malloc(26*sizeof(int));
    memset(hash, 0, 26*sizeof(int));

    for(int i=0;i<s_len;i++) {
        hash[s[i]-'a']++;
        hash[t[i]-'a']--;
    }
    for(int i=0;i<26;i++) {
        if(hash[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("start\n");

    printf("isAnagram: %d\n", isAnagram(test_s, test_t));

}
