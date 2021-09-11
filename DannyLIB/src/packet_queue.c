#include "packet_queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

void init_packet_queue(packet_queue_t *packet_queue, uint8_t *buf_p, uint32_t packet_sz, uint32_t queue_len) {
    packet_queue->enqueueIndex = 0;
    packet_queue->dequeueIndex = 0;
    packet_queue->packet_sz = packet_sz;
    packet_queue->count = 0;
    packet_queue->queue_len = queue_len;
    packet_queue->buf_len = queue_len*packet_sz;

    packet_queue->data = buf_p;
    assert(packet_queue->data != NULL);
}

void enqueue_packet(packet_queue_t *packet_queue, uint8_t *data) {
    if(packet_queue->queue_len > packet_queue->count) {
        memcpy(&packet_queue->data[packet_queue->enqueueIndex], data, packet_queue->packet_sz);
        packet_queue->enqueueIndex += packet_queue->packet_sz;
        if(packet_queue->enqueueIndex >= packet_queue->buf_len) {
            packet_queue->enqueueIndex = 0;
        }
        packet_queue->count++;
    }
    else {
        assert(0);
    }
    assert(packet_queue->queue_len >= packet_queue->count);
}

void dequeue_packet(packet_queue_t *packet_queue) {
    assert(packet_queue->count>0);
    if(packet_queue->count>0) {
        packet_queue->dequeueIndex += packet_queue->packet_sz;
        if(packet_queue->dequeueIndex >= packet_queue->buf_len) {
            packet_queue->dequeueIndex = 0;
        }
        packet_queue->count--;
    }
}


