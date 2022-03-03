#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


#define MAGIC_NUM   (31L)
#define MODULE_NUM  (100000L + 7L)
char test_str[] = "ababab";

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

/*
Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
*/
long hashstr(char *str1, char *str2, int length) {


    return 0;
}

bool repeatedSubstringPattern(char *s) {
    if(s == NULL) return false;
    int length = strlen(s);
    if(length == 0) return 0;

    for(int i=0;i<length;i++) {
        int substring_size = i + 1;

        if(length % substring_size != 0 || length == substring_size) {
            continue;
        }

        char *temp = (char *)malloc(substring_size * sizeof(char));
        memcpy(temp, &s[0], substring_size);

        bool ok_flag = true;
        for(int j=0;j<length;j+=substring_size) {
            /* Using C strncmp function */
            // if(strncmp(&s[j], temp, substring_size) != 0) {
            //     ok_flag = false;
            //     break;
            // }

            /* Using my hash function to compare two char array */
            if(hashstr(&s[j], temp, substring_size) != 0) {
                ok_flag = false;
                break;
            }
        }
        free(temp);
        
        if(ok_flag) return true;
    }

    return false;
}


int main(int argc, char *argv[]) {
    printf("%s: %d\n", test_str, repeatedSubstringPattern(test_str));
}

