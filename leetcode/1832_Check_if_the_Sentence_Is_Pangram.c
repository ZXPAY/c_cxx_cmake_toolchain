#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_string[] = "thequickbrownfoxjumpsoverthelazydog";  // true
char test_string[] = "leetcode";  // false

bool checkIfPangram(char *sentence) {
    int length = strlen(sentence);
    bool *alphabet_map = malloc(26*sizeof(bool));
    memset(alphabet_map, 0, 26*sizeof(bool));
    for(int i=0;i<length;i++) {
        if(sentence[i]<='z' && sentence[i]>='a')
            alphabet_map[sentence[i]-'a'] = true;
    }

    for(int i=0;i<26;i++) {
        if(!alphabet_map[i]) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %d\n", checkIfPangram(test_string));


}

