#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.
*/

#define TEST_N 4
int test_connections[][2] = {
    {0, 1},
    {1, 2},
    {2, 0},
    {1, 3}
};
#define CONNECTION_SIZE_OF(x) (sizeof(x) / sizeof(x[0]))


#define MIN(x, y) (x < y ? x : y)

typedef struct _linklist_ {
    int val;
    struct _linklist_ *next;
} linklist_t;

typedef struct _graph_node_ {
    int count;
    linklist_t *head;
    linklist_t *tail;
} graph_node_t;

linklist_t *generate_node(int val) {
    linklist_t *list = malloc(sizeof(linklist_t));
    list->val = val;
    list->next = NULL;

    return list;
}

void graph_node_push_back(graph_node_t *node, int val) {
    if(node->tail == NULL) {
        node->head = generate_node(val);
        node->tail = node->head;
        node->count++;
    }
    else {
        node->tail->next = generate_node(val);
        node->count++;
        node->tail = node->tail->next;
    }
}

int get_graph_neighbor_count(graph_node_t *node) {
    return node->count;
}

void print_neighbor_nodes(graph_node_t *node) {
    linklist_t *temp = node->head;
    printf("{");
    while(temp != NULL) {
        printf("%d,", temp->val);
        temp = temp->next;
    }
    printf("}\n");
}

void dfs(int u, int p, graph_node_t **graph, int n, int *disc, int *low, bool *visited, int *time, int **bridges, int *i_bridge) {
    disc[u] = ++(*time);
    low[u] = *time;
    visited[u] = true;
    linklist_t *node = graph[u]->head;
    while(node != NULL) {
        int v = node->val;
        node = node->next;
        if(v == p) continue;
        if(!visited[v]) dfs(v, u, graph, n, disc, low, visited, time, bridges, i_bridge);
        low[u] = MIN(low[u], low[v]);
        if(low[v] > disc[u]) {
            printf("find: %d, %d\n", u, v);
            bridges[*i_bridge][0] = u;
            bridges[*i_bridge][1] = v;
            (*i_bridge)++;
        }

    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **criticalConnections(int n, int **connections, int connectionsSize, int *connectionsColSize, int *returnSize, int **returnColumnSizes) {
    graph_node_t **graph = (graph_node_t **)malloc(n*sizeof(graph_node_t *));
    for(int i=0;i<n;i++) {
        graph[i] = (graph_node_t *)malloc(sizeof(graph_node_t));
        memset(graph[i], 0, sizeof(graph_node_t));
    }

    int *disc = (int *)malloc(n*sizeof(int));
    int *low = (int *)malloc(n*sizeof(int));
    bool *visited = (int *)malloc(n*sizeof(int));
    memset(disc, 0, n*sizeof(int));
    memset(low, 0, n*sizeof(int));
    memset(visited, 0, n*sizeof(int));

    /* critical anwser */
    int **bridges = (int **)malloc(n*sizeof(int *));
    *returnSize = 0;
    for(int i=0;i<n;i++) {
        bridges[i] = (int *)malloc(2*sizeof(int));
    }

    for(int i=0;i<connectionsSize;i++) {
        assert(connectionsColSize[i]==2);
        // a->b, b->a
        int a = connections[i][0];
        int b = connections[i][1];
        graph_node_push_back(graph[a], b);
        graph_node_push_back(graph[b], a);
    }

    /* print the neighbor nodes (graph) */
    for(int i=0;i<n;i++) {
        print_neighbor_nodes(graph[i]);
    }

    int time = 0;
    dfs(0, 0, graph, n, disc, low, visited, &time, bridges, returnSize);

    /* column */
    int *col_sz = malloc((*returnSize)*sizeof(int));
    for(int i=0;i<*returnSize;i++) {
        col_sz[i] = 2;
    }
    *returnColumnSizes = col_sz;


    return bridges;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%d\n", CONNECTION_SIZE_OF(test_connections));

    int sz = CONNECTION_SIZE_OF(test_connections);
    int **connections = malloc(sz*sizeof(int *));
    int *col_sz = malloc(sz*sizeof(int));
    for(int i=0;i<sz;i++) {
        connections[i] = malloc(2*sizeof(int));
        memcpy(connections[i], &test_connections[i][0], 2*sizeof(int));
        col_sz[i] = 2;
    }

    int return_sz = 0;
    int *return_col = NULL;
    int **result = criticalConnections(TEST_N, connections, sz, col_sz, &return_sz, &return_col);

    printf("result:\n");
    for(int i=0;i<return_sz;i++) {
        for(int j=0;j<return_col[i];j++) {
            printf("%d,", result[i][j]);
        }
        printf("\n");
    }
}

