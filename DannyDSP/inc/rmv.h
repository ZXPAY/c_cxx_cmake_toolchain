/**
 *
 *@brief: reculsvie moving average
*/
#ifndef RMV_H
#define RMV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rm_t {
    float *x;         // x[k]
    uint16_t M2;      // moving average window size
    float output;     // y[k]
    float attenuator; // attenuator
} rmv_t;


void init_rmv(rmv_t *rmv, float *x_buf, uint16_t M2);
float iter_rmv(rmv_t *rmv, float new_x);


#ifdef __cplusplus
}
#endif

#endif /* RMV_H */

