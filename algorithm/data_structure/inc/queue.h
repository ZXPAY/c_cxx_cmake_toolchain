#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>

/* Init queue maco */
#define MY_QUEUE_INIT     {   \
    .offer_i=0,               \
    .poll_i=0,                \
    .count=0                  \
    }

typedef enum queue_er_em {
    QUEUE_OK = 0,
    QUEUE_EMPTY = 1,
    QUEUE_FULL = 2,
    QUEUE_ERROR = 0xFF
} queue_er_em;

#define QUEUE_DEFINE(type, max_sz)                                         \
    typedef struct _queue_struct##type##_t {                               \
        type value[max_sz];                                                \
        int offer_i;                                                       \
        int poll_i;                                                        \
        int count;                                                         \
    } queue_##type##_t;                                                    \
    queue_er_em offer_queue_##type(queue_##type##_t *queue, type *tdata) { \
        if(queue->count >= max_sz) return QUEUE_FULL;                      \
        if(queue == NULL || tdata == NULL) return QUEUE_ERROR;             \
        memcpy(&queue->value[queue->offer_i++], tdata, sizeof(type));      \
        if(queue->offer_i == max_sz)  {                                    \
            queue->offer_i = 0;                                            \
        }                                                                  \
        queue->count++;                                                    \
        return QUEUE_OK;                                                   \
    }                                                                      \
    queue_er_em poll_queue_##type(queue_##type##_t *queue, type *rdata) {  \
        if(queue->count < 1) return QUEUE_EMPTY;                           \
        memcpy(rdata, &queue->value[queue->poll_i++], sizeof(type));       \
        if(queue->poll_i == max_sz)  {                                     \
            queue->poll_i = 0;                                             \
        }                                                                  \
        queue->count--;                                                    \
        return QUEUE_OK;                                                   \
    }                                                                      \
    inline int get_queue_size_##type(queue_##type##_t *queue) {            \
        return queue->count;                                               \
    }


#endif /* QUEUE_H */
