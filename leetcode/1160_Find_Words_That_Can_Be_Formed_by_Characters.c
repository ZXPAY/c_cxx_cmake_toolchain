#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


char test1_0[] = "cat";
char test1_1[] = "bt";
char test1_2[] = "hat";
char test1_3[] = "tree";
char test_char[] = "atach";


// char test1_0[] = "hello";
// char test1_1[] = "world";
// char test1_2[] = "leetcode";
// char test_char[] = "welldonehoneyr";

int countCharacters(char **words, int wordsSize, char *chars){
    int result = 0;
    int char_len = strlen(chars);

    int *hash = (int *)malloc(26*sizeof(int));
    memset(hash, 0, 26*sizeof(int));
    // hash the chars
    for(int i=0;i<char_len;i++) {
        hash[chars[i]-'a']++;
    }
    
    int *hash_word = (int *)malloc(26*sizeof(int));
    for(int i=0;i<wordsSize;i++) {
        int word_len = strlen(words[i]);
        memset(hash_word, 0, 26*sizeof(int));
        for(int k=0;k<word_len;k++) {
            hash_word[words[i][k]-'a']++;
        }
        // printf("===\n");
        int count = 0;
        for(int k=0;k<26;k++) {
            if(hash[k] >= hash_word[k] && hash[k] != 0) {
                // printf("match %c: %d, %d\n", k+'a', hash_word[k], hash[k]);
                count += hash_word[k];
            }
        }
        if(count == word_len) {
            result += count;
        }
    }

    free(hash);
    free(hash_word);

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int kk = 4;

    char **words = (char **)malloc(sizeof(char)*kk);
    for(int i=0;i<kk;i++) {
        words[i] = (char *)malloc(sizeof(char) * 100);
        memset(words[i], 0, 100);
    }

    memcpy(words[0], test1_0, sizeof(test1_0));
    memcpy(words[1], test1_1, sizeof(test1_1));
    memcpy(words[2], test1_2, sizeof(test1_2));
    memcpy(words[3], test1_3, sizeof(test1_3));


    printf("count: %d\n", countCharacters(words, kk, test_char));

}

