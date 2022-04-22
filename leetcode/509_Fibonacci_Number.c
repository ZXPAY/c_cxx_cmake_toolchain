#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>



int fib(int n) {
    if(n == 0) return 0;
    else if(n == 1 || n == 2) return 1;
    
    // f[k] = f[k-1] + f[k-2]
    int f1 = 1, f2 = 1;
    for(int i=0;i<n-2;i++) {
        int temp = f1;
        f1 = f1 + f2;
        f2 = temp;
    }
    
    return f1;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("n=10(ans=55): %d\n", fib(10));


}

