#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *generate_node(int val) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}


/* BFS solution start */
typedef struct TreeNode * queue_data_t;

typedef enum queue_er_em {
    QUEUE_OK = 0,
    QUEUE_EMPTY = 1,
    QUEUE_FULL = 2,
    QUEUE_ERROR = 0xFF
} queue_er_em;

typedef struct _queue_t {
    queue_data_t *value;
    int buf_size;
    int offer_i;
    int poll_i;
    int count;
} queue_t;

queue_t *create_queue(int buf_size) {
    queue_t *queue = malloc(sizeof(queue_t));
    memset(queue, 0, sizeof(queue_t));
    queue->buf_size = buf_size;
    queue->value = malloc(buf_size*sizeof(queue_data_t));
    memset(queue->value, 0, buf_size*sizeof(queue_data_t));

    return queue;
}

queue_er_em offer_queue(queue_t *queue, queue_data_t *tdata) {
    assert(queue->count < queue->buf_size);
    if(queue->count >= queue->buf_size) return QUEUE_ERROR;
    memcpy(&queue->value[queue->offer_i++], tdata, sizeof(queue_data_t));
    if(queue->offer_i == queue->buf_size) queue->offer_i = 0;
    queue->count++;
    return QUEUE_OK;
}

queue_er_em poll_queue(queue_t *queue, queue_data_t *rdata) {
    assert(queue->count > 0);
    if(queue->count < 1) return QUEUE_EMPTY;
    memcpy(rdata, &queue->value[queue->poll_i++], sizeof(queue_data_t));
    if(queue->poll_i == queue->buf_size) queue->poll_i = 0;
    queue->count--;
    return QUEUE_OK;
}

inline int get_queue_data_count(queue_t *queue) {
    return queue->count;
}

bool is_queue_empty(queue_t *queue) {
    return !(queue->count!=0);
}

int deepestLeavesSum_bfs(struct TreeNode *node) {
    if(node == NULL) return 0;
    int result = 0;
    queue_t *buf = create_queue(100);
    offer_queue(buf, &node);

    while(!is_queue_empty(buf)) {
        int count = get_queue_data_count(buf);
        result = 0;

        for(int i=0;i<count;i++) {
            poll_queue(buf, &node);
            result += node->val;

            if(node->left != 0) offer_queue(buf, &node->left);
            if(node->right != 0) offer_queue(buf, &node->right);
        }
    }

    return result;
}
/* BFS solution end */

/* DFS solution start */
void deepeastLeaves_dfs(struct TreeNode *node, int level, int *max_level, int *sum_deepest) {
    if(node == NULL) return;

    if(*max_level < level) {
        *max_level = level;
        *sum_deepest = 0;
    }

    deepeastLeaves_dfs(node->left, level+1, max_level, sum_deepest);
    deepeastLeaves_dfs(node->right, level+1, max_level, sum_deepest);

    if(level == *max_level) {
        *sum_deepest += node->val;
    }
}

int deepestLeavesSum(struct TreeNode *node) {
    if(node == NULL) return 0;
    int max_level = 0;
    int result = 0;
    deepeastLeaves_dfs(node, 0, &max_level, &result);
    // printf("max level: %d\n", max_level);

    return result;
}
/* DFS solution end */


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(1);
    root->left = generate_node(2);
    root->right = generate_node(3);

    root->left->left = generate_node(4);
    root->left->right = generate_node(5);

    root->right->right = generate_node(6);

    root->left->left->left = generate_node(7);
    root->right->right->right = generate_node(8);


    printf("result: %d\n", deepestLeavesSum_bfs(root));
    printf("result: %d\n", deepestLeavesSum(root));

}

