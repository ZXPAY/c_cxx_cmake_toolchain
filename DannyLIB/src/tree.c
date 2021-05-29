#include <stdio.h>
#include "tree.h"

void search(tree_node_t *n) {
    if(n != NULL) {
        printf("%p, %d\n", n, *((int *)n->para));
        
        search(n->left);
        search(n->right);
    }
}

void MorrisTraversal(tree_node_t* root) {
    tree_node_t *current, *pre;
 
    if (root == NULL)
        return;
 
    current = root;
    while (current != NULL) {
 
        if (current->left == NULL) {
            printf("=>%d ", *((int *)current->para));
            current = current->right;
        }
        else {
 
            /* Find the inorder predecessor of current */
            pre = current->left;
            while (pre->right != NULL
                   && pre->right != current)
                pre = pre->right;
 
            /* Make current as the right child of its
               inorder predecessor */
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
 
            /* Revert the changes made in the 'if' part to
               restore the original tree i.e., fix the right
               child of predecessor */
            else {
                pre->right = NULL;
                printf("%d ", *((int *)current->para));
                current = current->right;
            } /* End of if condition pre->right == NULL */
        } /* End of if condition current->left == NULL*/
        printf("%p\n", current);
    } /* End of while */
}
