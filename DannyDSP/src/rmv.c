#include <stdint.h>
#include "rmv.h"


void init_rmv(rmv_t *rmv, float *x_buf, uint16_t M2) {
    rmv->x = x_buf;
    rmv->M2 = M2;
    rmv->output = 0;
    rmv->attenuator = 1/(float)M2;
}

float iter_rmv(rmv_t *rmv, float new_x) {
    float x1 = rmv->attenuator * (new_x - rmv->x[0]);
    rmv->output += x1;

    // update the x buffer
    for(int i=0;i<rmv->M2-1;i++) {
        rmv->x[i] = rmv->x[i+1];
    } 
    rmv->x[rmv->M2-1] = new_x;   // update the newest data

    return rmv->output;
}

