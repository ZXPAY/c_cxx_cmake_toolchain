#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "relieve_stress.h"


extern relieve_stress_t relieve_stress;

int main() {

    printf("%d\n", time(NULL));

    register_relieve_stress(1, RELIEVE_PASS | 3, RELIEVE_INFLATE);
    register_relieve_stress(2, 1, RELIEVE_INFLATE);
    register_relieve_stress(3, RELIEVE_PASS | 1, RELIEVE_DEFLATE);
    register_relieve_stress(5, 1, RELIEVE_INFLATE);

    int cnt = 0;
    for(;;) {
        uint8_t a = is_next_pos();
        if(a != 0xFF) {
            printf("%d, %d, %d\n", a, relieve_stress.relieve_unit[a].pos, relieve_stress.relieve_unit[a].value);
            if(cnt++ > 10) {
                break;
            }
        }
    }
    


}

