#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct _p {
    union 
    {
        uint8_t reg;
        struct {
            uint8_t d0: 1;  // LSB
            uint8_t d1: 1;
            uint8_t d2: 1;
            uint8_t d3: 1;
            uint8_t d4: 1;
            uint8_t d5: 1;
            uint8_t p0: 1;
            uint8_t p1: 1;  // MSB
        } bits;
    };
} p_t;


// addr:   MSB <--------------------> LSB
void calculat_lin_parity(p_t *ap_addr) {
    ap_addr->bits.p0 = ap_addr->bits.d0^ap_addr->bits.d1^ap_addr->bits.d2^ap_addr->bits.d4;
    ap_addr->bits.p1 = !(ap_addr->bits.d1^ap_addr->bits.d3^ap_addr->bits.d4^ap_addr->bits.d5);
}


int main(void) {

    for(int i=0;i<=0x3F;i++) {
        p_t temp_p = {.reg = i};
        calculat_lin_parity(&temp_p);
        printf("0x%2x: %d, %d\n", i, temp_p.bits.p0, temp_p.bits.p1);
    }

}


