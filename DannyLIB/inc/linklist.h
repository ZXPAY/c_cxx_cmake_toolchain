#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct _node_t {
    struct _node_t *next;
    void *para;
} node_t;

#define ITERATE_LINKLIST_BEGIN(head_p, _node_p)      \
    {                                                \
        node_t *node_p = head_p;                     \
        _node_p = NULL;                              \
        for(;node_p->next!=NULL;node_p=_node_p) {    \
            _node_p = node_p->next;
#define ITERATE_LINKLIST_END       }}


void register_linklist(node_t *head_p, node_t *node_p, void *para);



#endif /* LINKLIST_H */
