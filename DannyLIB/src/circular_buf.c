#include <stdint.h>
#include <assert.h>
#include "circular_buf.h"


void circular_buf_init(circular_buf_t *circular_buf, uint8_t *buf_p, uint16_t len) {
    circular_buf->head_i = 0;
    circular_buf->tail_i = 0;
    circular_buf->count = 0;
    circular_buf->buf_p = buf_p;
    circular_buf->busy_flag = 0;
    circular_buf->maxlen = len;
}

uint8_t circular_buf_put(circular_buf_t *circular_buf, uint8_t *data_p, uint8_t data_sz) {
    circular_buf->busy_flag = 1;
    uint16_t next;

    for(int i=0;i<data_sz;i++) {
        next = circular_buf->head_i + 1;
        if(next >= circular_buf->maxlen) next = 0;
        if(next == circular_buf->tail_i) {
            circular_buf->busy_flag = 0;
            assert(0);
            return 1;
        }

        circular_buf->buf_p[circular_buf->head_i] = data_p[i];
        circular_buf->head_i = next;
        circular_buf->count++;
    }
    circular_buf->busy_flag = 0;
    return  0;
}

uint8_t circular_buf_pop(circular_buf_t *circular_buf, uint8_t *data_p, uint8_t data_sz) {
    if(circular_buf->busy_flag) return 2;
    uint16_t next;
    for(int i=0;i<data_sz;i++) {
        if(circular_buf->head_i == circular_buf->tail_i) {
            return 1;
        }
        next = circular_buf->tail_i + 1;
        if(next >= circular_buf->maxlen) next = 0;

        data_p[i] = circular_buf->buf_p[circular_buf->tail_i];
        circular_buf->tail_i = next;
        circular_buf->count--;
    }

    return  0;
}

uint16_t circular_buf_get_count(circular_buf_t *circular_buf) {
    return circular_buf->count;
}

