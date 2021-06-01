#include <stdio.h>
#include <stdlib.h>
#include <dblinklist.h>

void sum_deepest(struct _dbnode_t *n, int level, int *maxlevel, int *sum_d) {
    if(n != NULL) {
        sum_deepest(n->left, level+1, maxlevel, sum_d);
        sum_deepest(n->right, level+1, maxlevel, sum_d);

        printf("%d, %d, max: %d\n", level, *((int *)n->para), *maxlevel);
        // level change
        if((*maxlevel) < level) {
            *maxlevel = level;
            *sum_d = 0;
        }
        if(*maxlevel == level) {
            *sum_d += *((int *)n->para);
        }
    }
}


int main () {

    int root_para = 0;
    dbnode_t n_head = {.left = NULL, .right = NULL, .para = (int *)&root_para};

    int n1_para = 1;
    dbnode_t n1 = {.left = NULL, .right = NULL, .para = (int *)&n1_para};

    int n2_para = 2;
    dbnode_t n2 = {.left = NULL, .right = NULL, .para = (int *)&n2_para};

    int n3_para = 3;
    dbnode_t n3 = {.left = NULL, .right = NULL, .para = (int *)&n3_para};

    int n4_para = 4;
    dbnode_t n4 = {.left = NULL, .right = NULL, .para = (int *)&n4_para};

    int n5_para = 5;
    dbnode_t n5 = {.left = NULL, .right = NULL, .para = (int *)&n5_para};

    int n6_para = 6;
    dbnode_t n6 = {.left = NULL, .right = NULL, .para = (int *)&n6_para};

    int n7_para = 7;
    dbnode_t n7 = {.left = NULL, .right = NULL, .para = (int *)&n7_para};

    // Link the all node
    // n_head.left = &n1;
    // n1.left = &n2;
    // n1.right = &n3;
    // n3.left = &n4;

    // n_head.right = &n5;
    // n5.left = &n6;
    // n6.left = &n8;
    // n6.right = &n7;

    n_head.left = &n1;
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;

    n_head.right = &n5;
    n5.right = &n6;
    n6.right = &n7;

    int sumd = 0;
    int lv = 0;
    int max_lv = 0;
    sum_deepest(&n_head, lv, &max_lv, &sumd);
    printf("sum: %d\n", sumd);

}

