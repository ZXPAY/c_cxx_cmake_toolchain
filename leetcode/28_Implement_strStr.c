#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Implement strStr().
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
Clarification:
What should we return when needle is an empty string? This is a great question to ask during an interview.
For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
*/

// char haystack[] = "heooll";
// char needle[] = "ll";
// char haystack[] = "aaaaa";
// char needle[] = "bba";
// char haystack[] = "mississippi";
// char needle[] = "mississippi";
char haystack[] = "aabaaabaaac";
char needle[] = "abaaac";
// char haystack[] = "abbbbbaabbaabaabbbaaaaabbabbbabbbbbaababaabbaabbbbbababaababbbbaaabbbbabaabaaaabbbbabbbaabbbaabbaaabaabaaaaaaaa";
// char needle[] = "abbbaababbbabbbabbbbbabaaaaaaabaabaabbbbaabab";

#define MAGIC_NUM   (31L)
#define MODULE_NUM  (100000L + 7L)

long mod(long num, long m) {
    return (num % m + m) % m;
}

long hash(char *str_p, int length) {
    long result = 0;
    for(int i=0;i<length;i++) {
        result *= MAGIC_NUM;
        result += (long)str_p[i];
        result = mod(result, MODULE_NUM);
    }

    return result;
}

int strStr(char *haystack, char *needle) {
    if(haystack == NULL || needle == NULL) return -1;

    int hsy_len = strlen(haystack);
    int needle_len = strlen(needle);

    if(needle_len == 0) return 0;

    printf("needle hash: %ld\n", hash(needle, needle_len));
    long needle_hash = hash(needle, needle_len);

    long power = 1;
    for(int k=0;k<needle_len-1;k++) {
        power *= MAGIC_NUM;
        power = mod(power, MODULE_NUM);
    }
    long now_hash;

    for(int i=0;i<hsy_len-needle_len+1;i++) {
        if(i == 0) {
            /* Using hash function */
            now_hash = hash(&haystack[0], needle_len);
        }
        else {
            /* Using rolling hash */
            now_hash -= (long)haystack[i-1]*power;
            now_hash *= MAGIC_NUM;
            now_hash += (long)haystack[i+needle_len-1];

            now_hash = mod(now_hash, MODULE_NUM);
        }
        printf("=>%ld, %ld\n", now_hash, hash(&haystack[i], needle_len));
        if(now_hash == needle_hash) {
            /* Warning, it may occur the the same hash value */
            return i;
        }
    }    

    return -1;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("ans: %d\n", strStr(haystack, needle));
}

