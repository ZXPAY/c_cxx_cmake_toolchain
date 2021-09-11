#ifndef CIRCULAR_BUF_H
#define CIRCULAR_BUF_H

#include <stdint.h>

typedef struct _circular_buf_t {
  uint16_t head_i;
  uint16_t tail_i;
  uint8_t *buf_p;
  uint16_t count;
  uint16_t maxlen;
  uint8_t busy_flag;
} circular_buf_t;


void circular_buf_init(circular_buf_t *circular_buf, uint8_t *buf_p, uint16_t len);
uint8_t circular_buf_put(circular_buf_t *circular_buf, uint8_t *data_p, uint8_t data_sz);
uint8_t circular_buf_pop(circular_buf_t *circular_buf, uint8_t *data_p, uint8_t data_sz);
inline uint16_t circular_buf_get_count(circular_buf_t *circular_buf);

#endif /* CIRCULAR_BUF_H */
