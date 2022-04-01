#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_string[] = "123456";

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverseString(char* s, int sSize){
    for(int i=0;i<sSize>>1;i++) {
        swap(&s[i], &s[sSize-i-1]);
    } 
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int length = strlen(test_string);
    printf("Before: %s\n", test_string);
    reverseString(test_string, length);
    printf("After: %s\n", test_string);

}

