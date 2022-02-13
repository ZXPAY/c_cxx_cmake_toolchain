#ifndef STACK_LINKLIST_H
#define STACK_LINKLIST_H

#include <stdlib.h>

typedef enum stacklink_er_em {
    STACKLINK_OK = 0,
    STACKLINK_EMPTY = 1,
    STACKLINK_FULL = 2,
    STACKLINK_ERROR = 0xFF
} stacklink_er_em;

#define STACKLINK_DEFINE(type)                                                            \
    typedef struct _stacklink_node_##type##_t {                                           \
        struct _stacklink_node_##type##_t *next;                                          \
        type value;                                                                       \
    } stacklink_node_##type##_t;                                                          \
    typedef struct _stacklink_struct##type##_t {                                          \
        stacklink_node_##type##_t *head;                                                  \
        int count;                                                                        \
    } stacklink_##type##_t;                                                               \
    stacklink_er_em push_stacklink_##type(stacklink_##type##_t *stacklink, type *tdata) { \
        stacklink_node_##type##_t *node =                                                 \
            (stacklink_node_##type##_t *)malloc(sizeof(stacklink_node_##type##_t));       \
        node->next = NULL;                                                                \
        memcpy(&node->value, tdata, sizeof(type));                                        \
        if(stacklink->head == NULL) stacklink->head = node;                               \
        else {                                                                            \
            stacklink_node_##type##_t *tmp = stacklink->head;                             \
            stacklink->head = node;                                                       \
            stacklink->head->next = tmp;                                                  \
        }                                                                                 \
        stacklink->count++;                                                               \
        return STACKLINK_OK;                                                              \
    }                                                                                     \
    stacklink_er_em pop_stacklink_##type(stacklink_##type##_t *stacklink, type *rdata) {  \
        if(stacklink->head == NULL) return STACKLINK_EMPTY;                               \
        memcpy(rdata, &stacklink->head->value, sizeof(type));                             \
        stacklink_node_##type##_t *tmp = stacklink->head;                                 \
        stacklink->head = stacklink->head->next;                                          \
        free(tmp);                                                                        \
        stacklink->count--;                                                               \
        return STACKLINK_OK;                                                              \
    }                                                                                     \
    inline int get_stacklink_size_##type(stacklink_##type##_t *stacklink) {               \
        return stacklink->count;                                                          \
    }



#endif /* STACK_LINKLIST_H */
