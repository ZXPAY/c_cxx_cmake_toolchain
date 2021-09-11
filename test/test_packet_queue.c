#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "packet_queue.h"

typedef struct _lin_packet_t {
    uint8_t id;
    uint8_t data_size;
    uint8_t data[8];
} lin_packet_t;


// queue 10
#define QUEUE_SIZE 10
static uint8_t buf[sizeof(lin_packet_t)*QUEUE_SIZE];

packet_queue_t test_packet_queue;
int main() {
    memset(buf, 0, sizeof(buf));
    packet_queue_init(&test_packet_queue, buf, sizeof(lin_packet_t), QUEUE_SIZE);

    int cnt = 0;
    printf("======== Enqueue ========\n");
    for(int i=0;i<10;i++) {
        lin_packet_t test_packet;
        memset(&test_packet, 0, sizeof(lin_packet_t));
        test_packet.id = 0x12;
        test_packet.data_size = 2;
        test_packet.data[0] = cnt;
        test_packet.data[1] = cnt * 10;
        packet_queue_enqueue(&test_packet_queue, (uint8_t *)&test_packet);
        printf("count len: %d\n", test_packet_queue.count);
        cnt++;
    }

    printf("======== Dequeue ========\n");
    // pop the queue
    for(int i=0;i<10;i++) {
        lin_packet_t test_packet;
        packet_queue_get_packet(&test_packet_queue, (uint8_t *)&test_packet);
        printf("%d, %d, %d\n", test_packet.id, test_packet.data[0], test_packet.data[1]);
        packet_queue_dequeue(&test_packet_queue);
        printf("count len: %d\n", test_packet_queue.count);
    }

    return 0;
}

