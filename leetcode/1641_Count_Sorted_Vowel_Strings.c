#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/*
a -> aa, ae, ai, ao, au
e -> ee, ei, eo, eu
i -> ii, io, iu
0 -> oo, ou
u -> uu
*/



int countVowelStrings(int n) {
    int a = 1;
    int e = 1;
    int i = 1;
    int o = 1;
    int u = 1;
    for(int k=1;k<n;k++) {
        a = a + e + i + o + u;
        e = e + i + o + u;
        i = i + o + u;
        o = o + u;
    }
    return a + e + i + o + u;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }



    int result = countVowelStrings(1);
    printf("result( 5): %d\n", result);


    result = countVowelStrings(2);
    printf("result(15): %d\n", result);


}

