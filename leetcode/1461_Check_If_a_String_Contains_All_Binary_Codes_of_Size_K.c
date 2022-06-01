#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char *test_string = "00110110";
#define TEST_K  2

bool hasAllCodes(char *s, int k) {
    int length = strlen(s);
    if(length < k) return false;
    bool *myset = malloc((1<<k)*sizeof(bool));
    memset(myset, 0, (1<<k)*sizeof(bool));

    int temp = 0;
    int first = s[0] - '0';

    /* First to collect */
    for(int i=0;i<k;i++) {
        temp += (s[i] - '0') << i;
    }

    myset[temp] = 1;
    int cnt = 1;
    int mast = (1<<k) - 1;

    for(int i=k;i<length;i++) {
        temp -= first;
        temp >>= 1;
        temp += (s[i] - '0') << (k-1);
        first = s[i-k+1] - '0';
        if(myset[temp] == 0) {
            myset[temp] = 1;
            if(++cnt == (1<<k)) return true;
        }
        myset[temp] = 1;
    }

    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }



    printf("result: %d\n", hasAllCodes(test_string, TEST_K));


}

