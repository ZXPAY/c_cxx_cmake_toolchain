#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of instances that can be formed.

*/


#define TEXT  "balllllllllllloooooooooon"   // answer is 1

int getBalloonCharIndex(char ch) {
    switch (ch) {
        case 'b':
            return 0;
        case 'a':
            return 1;
        case 'l':
            return 2;
        case 'o':
            return 3;
        case 'n':
            return 4;
        default:
            break;
    }
    return -1;
}

int maxNumberOfBalloons(char *text){
    int *hash_map = (int *)malloc(5*sizeof(int));   // ballon, five letters
    memset(hash_map, 0, 5*sizeof(int));
    for(int i=0;i<strlen(text);i++) {
        int hash_i = getBalloonCharIndex(text[i]);
        if(hash_i != -1) {
            hash_map[hash_i]++;
        }
    }
    // l and o letter divide 2
    hash_map[2] >>= 1;
    hash_map[3] >>= 1;
    
    // Find the minimal counter
    int temp;
    for(int i=0;i<5;i++) {
        if(hash_map[i] == 0) return 0;
        if(i == 0) {
            temp = hash_map[i];
        }
        else if(temp > hash_map[i]) temp = hash_map[i];
    }
    free(hash_map);
    return temp;
}

int main() {
    printf("start\n");

    printf("maxNumberOfBalloons: %d\n", maxNumberOfBalloons(TEXT));
}
