#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <stdint.h>

typedef struct _packet_queue_ {
    uint8_t *data;          // point to the data
    uint32_t buf_len;       // queue buf length
    uint32_t enqueueIndex;  // queue index
    uint32_t dequeueIndex;  // dequeue index
    uint32_t packet_sz;     // each packet length
    uint16_t queue_len;     // queue length
    uint32_t count;         // how many data should be send
} packet_queue_t;

void packet_queue_init(packet_queue_t *packet_queue, uint8_t *buf_p, uint32_t packet_sz, uint32_t queue_len);
void packet_queue_enqueue(packet_queue_t *packet_queue, uint8_t *data);
void packet_queue_get_packet(packet_queue_t *packet_queue, uint8_t *packet);
void packet_queue_dequeue(packet_queue_t *packet_queue);
uint32_t packet_queue_get_count(packet_queue_t *packet_queue);

#endif /* PACKET_QUEUE_H */