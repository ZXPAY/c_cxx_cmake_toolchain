#ifndef DBLINKLIST_H
#define DBLINKLIST_H

typedef struct _dbnode_t {
    struct _dbnode_t *left;
    struct _dbnode_t *right;
    void *para;
} dbnode_t;


#define ITERATE_LINKLIST_BEGIN(head_p, _dbhead_p)         \
    {                                                     \
        dbnode_t *dbhead_p = head_p;                      \
        _dbhead_p = NULL;                                 \
        for(;dbhead_p->right!=NULL;dbhead_p=_dbhead_p) {  \
            _dbhead_p = dbhead_p->right;
#define ITERATE_LINKLIST_END       }}


void register_dblinklist(dbnode_t *head_p, dbnode_t *node_p, void *para);


#endif /* DBLINKLIST_H */
