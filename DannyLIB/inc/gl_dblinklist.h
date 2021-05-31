#ifndef GL_DBLINKLIST_H
#define GL_DBLINKLIST_H

#include <stdbool.h>

#define OFFSET_OF(struct_name, struct_field)   \
    (&((struct_name *)0)->struct_field)

typedef struct _gl_node_t {
    struct _gl_node_t *left;
    struct _gl_node_t *right;
} gl_node_t;

#define ITERATE_GL_LINKLIST_BEGIN(head_p, _node_p)      \
    {                                                \
        gl_node_t *node_p = head_p;                     \
        _node_p = NULL;                              \
        for(;node_p->right!=NULL;node_p=_node_p) {    \
            _node_p = node_p->right;
#define ITERATE_GL_LINKLIST_END       }}


#define ITERATE_GL_TREE_BEGIN(_head_p, _iter_node_p)                        \
    {                                                                    \
    gl_node_t *_pre_p, *_node_p;                                       \
    int _flag_search = false;                                            \
    _node_p = _head_p;                                                   \
    while (_node_p != NULL) {                                            \
        _flag_search = false;                                            \
        if (_node_p->left == NULL) {                                     \
            _iter_node_p = _node_p;                                      \
            _node_p = _node_p->right;                                    \
            _flag_search = true;                                         \
        }                                                                \
        else {                                                           \
            _pre_p = _node_p->left;                                      \
            while (_pre_p->right != NULL && _pre_p->right != _node_p) {  \
                _pre_p = _pre_p->right;                                  \
            }                                                            \
            if (_pre_p->right == NULL) {                                 \
                _pre_p->right = _node_p;                                 \
                _node_p = _node_p->left;                                 \
            }                                                            \
            else {                                                       \
                _pre_p->right = NULL;                                    \
                _iter_node_p = _node_p;                                  \
                _node_p = _node_p->right;                                \
                _flag_search = true;                                     \
            } /* End of if condition _pre_p->right == NULL */            \
        } /* End of if condition _node_p->left == NULL*/                 \
        if(_flag_search && _iter_node_p != NULL) {
#define ITERATE_GL_TREE_END       }}}

void insert_gllinklist(gl_node_t *node1_p, gl_node_t *node2_p);

#endif /* GL_DBLINKLIST_H */
