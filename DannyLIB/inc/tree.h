#ifndef DB_LINKLITREE_HST_H
#define TREE_H

typedef struct _tree_node_t {
    struct _node_t *parent;
    struct _node_t *left;
    struct _node_t *right;
    void *para;
} tree_node_t;


#define ITERATE_LINKLIST_BEGIN(head_p, _node_p)      \
    {                                                \
        tree_node_t *tree_head_p = head_p;                     \
        _node_p = NULL;                              \
        for(;tree_head_p->right!=NULL;tree_head_p=_node_p) {    \
            _node_p = tree_head_p->right;
#define ITERATE_LINKLIST_END       }}




#endif /* TREE_H */
