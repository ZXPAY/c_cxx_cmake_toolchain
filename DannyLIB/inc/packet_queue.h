#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <stdint.h>

typedef struct _packet_queue_ {
    uint8_t *data;          // point to the data
    uint32_t buf_len;       // queue buf length
    uint32_t enqueueIndex;  // queue index
    uint32_t dequeueIndex;  // dequeue index
    uint32_t packet_sz;     // each notify data length
    uint16_t queue_len;     // queue length
    uint32_t count;         // how many data should be send
} packet_queue_t;

void init_packet_queue(packet_queue_t *packet_queue, uint8_t *buf_p, uint32_t packet_sz, uint32_t queue_len);
void enqueue_packet(packet_queue_t *packet_queue, uint8_t *data);
void dequeue_packet(packet_queue_t *packet_queue);


#endif /* PACKET_QUEUE_H */