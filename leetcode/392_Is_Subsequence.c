#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// #define MAIN_SEQ "ahbgdc"
// #define SUB_SEQ  "abc"
#define MAIN_SEQ "ahbgdc"
#define SUB_SEQ  "axc"

bool isSubsequence(char *s, char *t){
    int cnt_s = 0;
    for(int i=0;i<strlen(t);i++) {
        if(t[i] == s[cnt_s]) {
            cnt_s++;
        }
    }
    if(cnt_s == strlen(s)) {
        return true;
    }
    return false;
}

int main() {
    printf("start\n");

    char *s = SUB_SEQ;
    char *t = MAIN_SEQ;

    printf("%s is sub sequence of %s, isSubsequence: %d\n", s ,t, isSubsequence(s, t));

}
