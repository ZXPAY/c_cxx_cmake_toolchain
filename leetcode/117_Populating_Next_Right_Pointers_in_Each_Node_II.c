#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.
*/


/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct Node *generate_node(int val) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;

    return node;
}


typedef struct Node * queue_data_t;

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
    memset(queue->value, 0, buf_size*sizeof(queue));

    return queue;
}

queue_er_em offer_queue(queue_t *queue, queue_data_t *tdata) {
    if(queue->count >= queue->buf_size) return QUEUE_ERROR;
    memcpy(&queue->value[queue->offer_i++], tdata, sizeof(queue_data_t));
    if(queue->offer_i == queue->buf_size) queue->offer_i = 0;
    queue->count++;
    return QUEUE_OK;
}

queue_er_em poll_queue(queue_t *queue, queue_data_t *rdata) {
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

struct Node *connect(struct Node *root) {
    if(root == NULL) return NULL;
    queue_t *buf = create_queue(500);
    struct Node *node = root;

    /* Using BFS, first init */
    if(node->left != NULL) {
        offer_queue(buf, &node->left);
    }
    if(node->right != NULL) {
        offer_queue(buf, &node->right);
    }

    while(!is_queue_empty(buf)) {
        int count = get_queue_data_count(buf);
        struct Node *prev = NULL;
        for(int i=0;i<count;i++) {
            poll_queue(buf, &node);
            if(prev != NULL) {
                prev->next = node;
            }
            prev = node;

            if(node->left != NULL) {
                offer_queue(buf, &node->left);
            }
            if(node->right != NULL) {
                offer_queue(buf, &node->right);
            }
        }
    }

    return root;
}


void print_next(struct Node *node) {
    if(node == NULL) return;

    if(node->next == NULL) {
        printf("%d => NULL\n", node->val);
    }
    else {
        printf("%d => %d\n", node->val, node->next->val);
    }


    print_next(node->left);
    print_next(node->right);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct Node *node = generate_node(1);

    node->left = generate_node(2);
    node->right = generate_node(3);
    node->left->left = generate_node(4);
    node->left->right = generate_node(5);
    node->right->right = generate_node(7);


    print_next(connect(node));

}

