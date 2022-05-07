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
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

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

bool isSymmetric_bfs(struct TreeNode *root) {
    if(root->left == NULL && root->right == NULL) {
        return true;
    }
    else if(root->left == NULL || root->right == NULL) {
        return false;
    }

    /* BFS the node */
    queue_t *buf_l = create_queue(50);
    queue_t *buf_r = create_queue(50);

    offer_queue(buf_l, &root->left);
    offer_queue(buf_r, &root->right);

    while((get_queue_data_count(buf_l)) || get_queue_data_count(buf_r)) {

        struct TreeNode *nl = NULL;
        struct TreeNode *nr = NULL;
        poll_queue(buf_l, &nl);
        poll_queue(buf_r, &nr);

        if(nl != NULL && nr != NULL) {
            // printf("%d,%d\n", nl->val, nr->val);
            if(nl->val != nr->val) {
                return false;
            }
        }
        else {
            return false;
        }

        if(nl->left != NULL && nr->right != NULL) {
            offer_queue(buf_l, &nl->left);
            offer_queue(buf_r, &nr->right);
        }
        else if(nl->left != NULL || nr->right != NULL) {
            return false;
        }
        if(nl->right != NULL && nr->left != NULL) {
            offer_queue(buf_l, &nl->right);
            offer_queue(buf_r, &nr->left);
        }
        else if(nl->right != NULL || nr->left != NULL) {
            return false;
        }
    }

    return true;
}

bool isSymmetric_help(struct TreeNode *n1, struct TreeNode *n2) {
    if(n1 == NULL || n2 == NULL) return true;

    if(n1->val != n2->val) return false;

    /* n1 go left,  n2 go right */
    if(n1->left != NULL && n2->right != NULL) {
        if(isSymmetric_help(n1->left, n2->right) == false) {
            return false;
        }
    }
    else if(n1->left != NULL || n2->right != NULL) {
        return false;
    }
    /* n1 go right, n1 go left */
    if(n1->right != NULL && n2->left != NULL) {
        if(isSymmetric_help(n1->right, n2->left) == false) {
            return false;
        }
    }
    else if(n1->right != NULL || n2->left != NULL) {
        return false;
    }

    return true;
}

bool isSymmetric(struct TreeNode *root) {
    if(root->left == NULL && root->right == NULL) {
        return true;
    }
    if(root->left != NULL && root->right != NULL) {
        return isSymmetric_help(root->left, root->right);
    }
    return false;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct TreeNode *root = generate_node(1);
    root->left = generate_node(2);
    root->right = generate_node(2);

    root->left->left = generate_node(3);
    root->left->right = generate_node(4);

    root->right->left = generate_node(4);
    root->right->right = generate_node(3);


    printf("result: %d\n", isSymmetric(root));



}

