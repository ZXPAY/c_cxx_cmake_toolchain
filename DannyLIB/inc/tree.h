#ifndef DB_LINKLITREE_HST_H
#define TREE_H

#include <stdbool.h>

typedef struct _tree_node_t {
    struct _tree_node_t *parent;
    struct _tree_node_t *left;
    struct _tree_node_t *right;
    void *para;
} tree_node_t;


#define ITERATE_TREE_BEGIN(_head_p, _iter_node_p)                        \
    {                                                                    \
    tree_node_t *_pre_p, *_node_p;                                       \
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
#define ITERATE_TREE_END       }}}

void search(tree_node_t *n);
tree_node_t find_tree_most_left();
void MorrisTraversal(tree_node_t* _head_p);

#endif /* TREE_H */
