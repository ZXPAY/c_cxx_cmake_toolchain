#ifndef STACK_H
#define STACK_H

#include <string.h>

/* Init stack maco */
#define MY_STACK_INIT     {   \
    .stack_i=0                \
    }

typedef enum stack_er_em {
    STACK_OK = 0,
    STACK_EMPTY = 1,
    STACK_FULL = 2,
    STACK_ERROR = 0xFF
} stack_er_em;

#define STACK_DEFINE(type, max_sz)                                             \
    typedef struct _stack_struct##type##_t {                                   \
        type value[max_sz];                                                    \
        int stack_i;                                                           \
    } stack_##type##_t;                                                        \
    stack_er_em push_stack_##type(stack_##type##_t *stack, type *tdata) {      \
        if(stack->stack_i >= max_sz) return STACK_FULL;                        \
        if(stack == NULL || tdata == NULL) return STACK_ERROR;                 \
        memcpy(&stack->value[stack->stack_i++], tdata, sizeof(type));          \
        return STACK_OK;                                                       \
    }                                                                          \
    stack_er_em pop_stack_##type(stack_##type##_t *stack, type *rdata) {       \
        if(stack->stack_i < 1) return STACK_EMPTY;                             \
        memcpy(rdata, &stack->value[stack->stack_i-1], sizeof(type));          \
        stack->stack_i--;                                                      \
        return STACK_OK;                                                       \
    }                                                                          \
    inline int get_stack_size_##type(stack_##type##_t *stack) {                       \
        return stack->stack_i;                                                 \
    }


#endif /* STACK_H */
