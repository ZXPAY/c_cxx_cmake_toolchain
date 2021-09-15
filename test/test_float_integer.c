#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int main(void) {
    int min24 = (0x800000 << 8)/256;  //  -(((~d)&0x00FFFFFF)+1)
    printf("%d\n", min24);
    int max24 = 0x7FFFFF;
    printf("%d\n", max24);

    for(int i=min24;i<=max24;i++) {
        int32_t a = i;
        float b = (float)a*1.0f;
        int32_t c = (int32_t)b;
        // printf("%d\n", c);
        assert(a == c);
    }

    return 0;
}

