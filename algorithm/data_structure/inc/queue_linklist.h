#ifndef QUEUE_LINKLIST_H
#define QUEUE_LINKLIST_H

#include <stdlib.h>

typedef enum queuelink_er_em {
    QUEUELINK_OK = 0,
    QUEUELINK_EMPTY = 1,
    QUEUELINK_FULL = 2,
    QUEUELINK_ERROR = 0xFF
} queuelink_er_em;

#define QUEUELINK_DEFINE(type)                                                                \
    typedef struct _queuelink_node_##type##_t {                                               \
        struct _queuelink_node_##type##_t *next;                                              \
        type value;                                                                           \
    } queuelink_node_##type##_t;                                                              \
    typedef struct _queuelink_struct##type##_t {                                              \
        queuelink_node_##type##_t *head;                                                      \
        queuelink_node_##type##_t *tail;                                                      \
        int count;                                                                            \
    } queuelink_##type##_t;                                                                   \
    queuelink_er_em offer_queuelink_##type(queuelink_##type##_t *queuelink, type *tdata) {    \
        queuelink_node_##type##_t *node =                                                     \
            (queuelink_node_##type##_t *)malloc(sizeof(queuelink_node_##type##_t));           \
        node->next = NULL;                                                                    \
        memcpy(&node->value, tdata, sizeof(type));                                            \
        if(queuelink->head == NULL) {                                                         \
            queuelink->head = node;                                                           \
            queuelink->tail = node;                                                           \
        }                                                                                     \
        else {                                                                                \
            queuelink->tail->next = node;                                                     \
            queuelink->tail = node;                                                           \
        }                                                                                     \
        queuelink->count++;                                                                   \
        return QUEUELINK_OK;                                                                  \
    }                                                                                         \
    queuelink_er_em poll_queuelink_##type(queuelink_##type##_t *queuelink, type *rdata) {     \
        if(queuelink->head == NULL) return QUEUELINK_EMPTY;                                   \
        memcpy(rdata, &queuelink->head->value, sizeof(type));                                 \
        queuelink_node_##type##_t *tmp = queuelink->head;                                     \
        queuelink->head = queuelink->head->next;                                              \
        free(tmp);                                                                            \
        queuelink->count--;                                                                   \
        return QUEUELINK_OK;                                                                  \
    }                                                                                         \
    inline int get_queuelink_size_##type(queuelink_##type##_t *queuelink_) {                  \
        return queuelink_->count;                                                             \
    }


#endif /* QUEUE_LINKLIST_H */
