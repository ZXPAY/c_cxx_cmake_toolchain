#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* ans: 7.0, 0.5, -1.0, 1.0, -1.0 */
// char *test_string[][2] = {{"a", "b"}, {"b", "c"}};
// char *test_queries[][2] = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
// double value[] = {2.0, 3.0};

/* ans: 3.75, 0.4, 5, 0.2 */
// char *test_string[][2] = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
// char *test_queries[][2] = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
// double value[] = {1.5, 2.5, 5.0};

/* ans: 360.00000,0.00833,20.00000,1.00000,-1.00000,-1.00000 */
char *test_string[][2] = {{"x1","x2"},{"x2","x3"},{"x3","x4"},{"x4","x5"}};
char *test_queries[][2] = {{"x1","x5"},{"x5","x2"},{"x2","x4"},{"x2","x2"},{"x2","x9"},{"x9","x9"}};
double value[] = {3.0,4.0,5.0,6.0};

#define M   (sizeof(test_string) / sizeof(test_string[0]))
#define N   (sizeof(test_string) / M / sizeof(char *))

#define QM  (sizeof(test_queries) / sizeof(test_queries[0]))
#define QN  (sizeof(test_queries) / QM / sizeof(char *))

#define MAGIC_NUM     31L
#define MODULE_NUM    10000007L

long magic_array[5] = {31, 31*31, 31*31*31, 31*31*31*31, 31*31*31*31*31};

int find(int *rt, double **wt, int x) {
    int rx = rt[x];
    if (rx == x){
        return x;
    }
    rt[x] = find(rt, wt, rx);
    if (rt[x] != rx) {
        wt[x][rt[x]] = wt[x][rx] * wt[rx][rt[x]];
        wt[rt[x]][x] = 1.0/(wt[x][rt[x]]);
//        printf("x %d rx %d, rt[x] %d, wt[x][rt[x]] %f, wt[x][rx] %f  wt[rx][rt[x]] %f \n", x, rx, rt[x], wt[x][rt[x]], wt[x][rx],  wt[rx][rt[x]]);
    }
    return (rt[x]);
}

void ulink(int *rt, int *rnk, double **wt, double w, int x, int y) {
    int rx, ry;
    rx = find(rt, wt, x);
    ry = find(rt, wt, y);
    wt[x][y] = w;
    wt[y][x] = 1.0/w;
    if (rx == ry) return;
    wt[rx][ry] = wt[rx][x] * wt[y][ry] *wt[x][y];
    wt[ry][rx] = 1/(wt[rx][ry]);
    if (rnk[rx] > rnk[ry]){
        rt[ry] = rx;
    }else if (rnk[ry] > rnk[rx]){
        rt[rx] = ry;
    }else{
        rt[ry] = rx;
        rnk[rx] += 1;
    }
//    printf("x %d y %d rx %d, ry %d rt[rx] %d rt[ry] %d ", x, y, rx, ry, rt[rx], rt[ry]);
//    printf("wt[%d][%d] %f wt[%d][%d] %f wt[rx][x] %f , w %f\n", rx, ry, wt[rx][ry], ry, rx,wt[ry][rx],  wt[rx][x], w);
    return;
}

long mod(long n, long m) {
    return (n % m + m) % m;
}

long hash(char *charater) {
    int len = strlen(charater);
    long hash_value = 0;

    for(int i=0;i<len;i++) {
        hash_value += magic_array[i]*charater[i];
        hash_value = mod(hash_value, MODULE_NUM);
    }

    return hash_value;
}


typedef struct _node_t {
    struct _node_t *left;
    struct _node_t *right;
    long hash_val;
    int index;
} node_t;

node_t *generate_node(long hash_val, int index) {
    node_t *node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->hash_val = hash_val;
    node->index = index;

    return node;
}

node_t *insert_bst(node_t *node, long hash_val, int index, node_t **insert_node) {
    if(node == NULL) {
        // end node
        node = generate_node(hash_val, index);
        *insert_node = node;
        return node;
    }

    if(node->hash_val == hash_val) {
        return NULL;
        // assert(0);
    }
    else if(hash_val < node->hash_val) {
        // go left
        node_t *temp = insert_bst(node->left, hash_val, index, insert_node);
        if(temp != node->left) {
            node->left = temp;
            *insert_node = temp;
        }
    }
    else if(hash_val > node->hash_val) {
        // go right
        node_t *temp = insert_bst(node->right, hash_val, index, insert_node);
        if(temp != node->right) {
            node->right = temp;
            *insert_node = temp;
        }
    }

    return node;
}

node_t *search_in_bst(node_t *node, long hash_val) {
    if(node == NULL) return NULL;

    if(hash_val == node->hash_val) {
        return node;
    }
    if(hash_val < node->hash_val) {
        // go left
        return search_in_bst(node->left, hash_val);
    }
    else if(hash_val > node->hash_val) {
        // go right
        return search_in_bst(node->right, hash_val);
    }
    else {
        return NULL;
    }
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *calcEquation(char ***equations, int equationsSize, int *equationsColSize, double *values, int valuesSize, char *** queries, int queriesSize, int *queriesColSize, int *returnSize) {
    if(equationsSize != valuesSize) return NULL;
    double *result = malloc(queriesSize*sizeof(double));
    int *parent = malloc(equationsSize*2*sizeof(int));
    int *rank = malloc(equationsSize*2*sizeof(int));
    for(int i=0;i<equationsSize*2;i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    /* Mapping the equation string to 0~eqationsSize-1 */
    node_t *root = NULL;
    node_t *temp = NULL;
    int count = 0;
    for(int i=0;i<equationsSize;i++) {
        for(int j=0;j<equationsColSize[i];j++) {
            long hash_val = hash(equations[i][j]);
            printf("%s(%ld), ", equations[i][j], hash_val);
            if(search_in_bst(root, hash_val) == NULL) {
                root = insert_bst(root, hash_val, count, &temp);
                count++;
            }
        }
        printf("\n");
    }

    /* Generate the graph table (Adjacency matrix) */
    double **search_calc_table = malloc(equationsSize*2*sizeof(double *));
    for(int i=0;i<equationsSize*2;i++) {
        search_calc_table[i] = malloc(equationsSize*2*sizeof(double));
        for(int j=0;j<equationsSize*2;j++) {
            if(i==j) search_calc_table[i][j] = 1.0;
            else search_calc_table[i][j] = 0.0;
        }
    }

    node_t *n1 = NULL;
    node_t *n2 = NULL;
    /* Put the equation to table */
    for(int i=0;i<equationsSize;i++) {
        // col is always 2
        n1 = search_in_bst(root, hash(equations[i][0]));
        n2 = search_in_bst(root, hash(equations[i][1]));
        assert(n1 != NULL);
        assert(n2 != NULL);

        int i1 = n1->index;
        int i2 = n2->index;
        ulink(parent, rank, search_calc_table, values[i], i1, i2);
    }

    printf("Print calc table\n");
    for(int i=0;i<equationsSize*2;i++) {
        for(int j=0;j<equationsSize*2;j++) {
            printf("%10.5f, ", search_calc_table[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<queriesSize;i++) {
        n1 = search_in_bst(root, hash(queries[i][0]));
        n2 = search_in_bst(root, hash(queries[i][1]));
        if(n1 == NULL || n2 == NULL) {
            result[i] = -1.0;
            continue;
        }
        
        int i1 = n1->index;
        int i2 = n2->index;
        if(search_calc_table[i1][i2] > 1e-5) {
            result[i] = search_calc_table[i1][i2];
        }
        else {
            int x =  find(parent, search_calc_table, i1);
            int y =  find(parent, search_calc_table, i2);
            if(x == y) {
                result[i] = search_calc_table[i1][x]*search_calc_table[x][i2];
            }
            else {
                result[i] = -1.0;
            }
        }
    }

    *returnSize = queriesSize;
    return result;;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("Equation size: %d, %d\n", M, N);
    printf("Queries size: %d, %d\n", QM, QN);

    /* Build equation */
    char ***equation = malloc(M*sizeof(char **));
    int *col = malloc(M*sizeof(int));
    for(int i=0;i<M;i++) {
        equation[i] = malloc(N*sizeof(char *));
        col[i] = N;
        for(int j=0;j<N;j++) {
            int len = strlen(test_string[i][j]);
            equation[i][j] = malloc(len*sizeof(char));
            memcpy(equation[i][j], test_string[i][j], len);
        }
    }

    /* Build queries */
    char ***queries = malloc(QM*sizeof(char **));
    int *qcol = malloc(QM*sizeof(int));
    for(int i=0;i<QM;i++) {
        queries[i] = malloc(QN*sizeof(char *));
        qcol[i] = QN;
        for(int j=0;j<QN;j++) {
            int len = strlen(test_queries[i][j]);
            queries[i][j] = malloc(len*sizeof(char));
            memcpy(queries[i][j], test_queries[i][j], len);
        }
    }

    int return_sz = 0;
    double *result = calcEquation(equation, M, col, value, M, queries, QM, qcol, &return_sz);

    if(result == NULL) return 0;

    printf("{");
    for(int i=0;i<return_sz;i++) {
        printf("%.5f, ", result[i]);
    }
    printf("}\n");


}

