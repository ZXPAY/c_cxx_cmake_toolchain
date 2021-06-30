#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
You are given a string word that consists of digits and lowercase English letters.

You will replace every non-digit character with a space. For example, "a123bc34d8ef34" will become " 123  34 8  34". Notice that you are left with some integers that are separated by at least one space: "123", "34", "8", and "34".

Return the number of different integers after performing the replacement operations on word.

Two integers are considered different if their decimal representations without any leading zeros are different.

Constrain
1 <= word.length <= 1000
*/

char test_str[] = "a123bc34d8ef34";
// answer is 3, "123", "34", and "8". Notice that "34" is only counted once.


int numDifferentIntegers(char *word){
    int count = 0;
    int str_len = strlen(word);
    char *temp = (char *) malloc(str_len*sizeof(char));
    uint32_t *hash_map = (uint32_t *) malloc((str_len>>1)*sizeof(uint32_t));
    int c_h = 0;
    uint32_t hash = 0;
    int ck_flag = false;
    int flag = 0;
    for(int i=0;i<str_len;i++) {
        if(word[i] <= '9' && word[i] >= '0') {
            hash = hash*31 + (word[i]-'0');
            ck_flag = true;
        }
        else {
            if(ck_flag) {
                flag = 0;
                for(int j=0;j<c_h;j++) {
                    if(hash_map[j] == hash) {
                        flag = 1;
                        break;
                    }
                }
                if(!flag) {
                    count++;
                    hash_map[c_h++] = hash;
                }
                hash = 0;
                ck_flag = false;
            }
        }
    }
    int zero_cnt = 0;
    if(ck_flag) {
        flag = 0;
        for(int j=0;j<c_h;j++) {
            if(hash_map[j] == 0) zero_cnt++;
            if(hash_map[j] == hash) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            count++;
            hash_map[c_h++] = hash;
        }
        hash = 0;
    }

    free(temp);
    free(hash_map);
    if(c_h == 0) return 0;
    if(zero_cnt == c_h) return 1;
    return count;
}

int main() {
    printf("start\n");

    printf("numDifferentIntegers: %d\n", numDifferentIntegers(test_str));

}
