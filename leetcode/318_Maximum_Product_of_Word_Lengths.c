#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char *test_words[] = {
//     "abcw","baz","foo","bar","xtfn","abcdef"
// };
char *test_words[] = {
    "a","ab","abc","d","cd","bcd","abcd"
};

#define WORD_SIZE (sizeof(test_words) / sizeof(test_words[0]))

int maxProduct(char ** words, int wordsSize){

    int *words_use_bit = (int *)malloc(wordsSize*sizeof(int));
    memset(words_use_bit, 0, wordsSize*sizeof(int));

    for(int i=0;i<wordsSize;i++) {
        for(int j=0;j<strlen(words[i]);j++) {
            words_use_bit[i] |= 1<<(words[i][j]-'a');
        }
    }

    int result = 0;
    for(int i=0;i<wordsSize;i++) {
        for(int j=1;j<wordsSize;j++) {
            if(!(words_use_bit[i]&words_use_bit[j])) {
                int temp = strlen(words[i]) * strlen(words[j]);
                if(temp > result) {
                    result = temp;
                }
            }
        }
    }

    return result;
}


int main() {
    printf("result: %d\n", maxProduct(test_words, WORD_SIZE));

    return 0;
}

