#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {1, 3, 2, 5};    // 2
int test_array[] = {1,3,2,5,3,0,9}; //4
#define ARRAY_SIZE  ((sizeof(test_array) / sizeof(int)))

/*
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed integer.
*/


typedef enum queuelink_er_em {
    QUEUELINK_OK = 0,
    QUEUELINK_EMPTY = 1,
    QUEUELINK_FULL = 2,
    QUEUELINK_ERROR = 0xFF
} queuelink_er_em;

#define QUEUELINK_DEFINE(type)                                                                \
    typedef struct _queuelink_node_##type##_t {                                               \
        struct _queuelink_node_##type##_t *next;                                              \
        type value;                                                                           \
    } queuelink_node_##type##_t;                                                              \
    typedef struct _queuelink_struct##type##_t {                                              \
        queuelink_node_##type##_t *head;                                                      \
        queuelink_node_##type##_t *tail;                                                      \
        int count;                                                                            \
    } queuelink_##type##_t;                                                                   \
    queuelink_er_em offer_queuelink_##type(queuelink_##type##_t *queuelink, type *tdata) {    \
        if(tdata == NULL) return QUEUELINK_ERROR;                                             \
        queuelink_node_##type##_t *node =                                                     \
            (queuelink_node_##type##_t *)malloc(sizeof(queuelink_node_##type##_t));           \
        node->next = NULL;                                                                    \
        memcpy(&node->value, tdata, sizeof(type));                                            \
        if(queuelink->head == NULL) {                                                         \
            queuelink->head = node;                                                           \
            queuelink->tail = node;                                                           \
        }                                                                                     \
        else {                                                                                \
            queuelink->tail->next = node;                                                     \
            queuelink->tail = node;                                                           \
        }                                                                                     \
        queuelink->count++;                                                                   \
        return QUEUELINK_OK;                                                                  \
    }                                                                                         \
    queuelink_er_em poll_queuelink_##type(queuelink_##type##_t *queuelink, type *rdata) {     \
        if(queuelink->head == NULL) return QUEUELINK_EMPTY;                                   \
        memcpy(rdata, &queuelink->head->value, sizeof(type));                                 \
        queuelink_node_##type##_t *tmp = queuelink->head;                                     \
        queuelink->head = queuelink->head->next;                                              \
        free(tmp);                                                                            \
        queuelink->count--;                                                                   \
        return QUEUELINK_OK;                                                                  \
    }                                                                                         \
    inline int get_queuelink_size_##type(queuelink_##type##_t *queuelink_) {                  \
        return queuelink_->count;                                                             \
    }

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode node_data;
QUEUELINK_DEFINE(node_data);

int widthOfBinaryTree(struct TreeNode *root) {
    queuelink_node_data_t myqueue = {.head = NULL, .tail = NULL, .count = 0};

    offer_queuelink_node_data(&myqueue, root);

    // BFS
    long left = 0;
    long right = 0;
    node_data tmp;
    int result = 0;
    while(true) {
        int counts = get_queuelink_size_node_data(&myqueue);
        if(0 == counts) break;

        for(int i=0;i<counts;i++) {
            poll_queuelink_node_data(&myqueue, &tmp);
            if(0 == i) {
                left = tmp.val;
            }
            right = tmp.val;

            if(tmp.left != NULL) {
                tmp.left->val = tmp.val * 2L;
                offer_queuelink_node_data(&myqueue, tmp.left);
            }
            if(tmp.right != NULL) {
                tmp.right->val = tmp.val * 2L + 1;
                offer_queuelink_node_data(&myqueue, tmp.right);
            }

            int temp_res = right - left + 1;
            if(result < temp_res) {
                result = temp_res;
            }
            printf("%ld, %ld => %d\n", left, right, temp_res);
        }

    }

    return result;
}

int main(int argc, char *argv[]) {
    /* Build the tree */
    struct TreeNode *node[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i++) {
        if(test_array[i] == 0) {
            node[i] = NULL;
            continue;
        }
        node[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        node[i]->left = NULL;
        node[i]->right = NULL;
        node[i]->val = test_array[i];
    }

    struct TreeNode *root = node[0];

    for(int i=0;i<ARRAY_SIZE-1;i++) {
        int i_left = (i + 1) * 2 - 1; 
        int i_right = (i + 1) * 2;

        // if(test_array[i] == 0) continue;

        struct TreeNode *temp = node[i];
        if(temp != NULL) {
            if(i_left < ARRAY_SIZE) {
                temp->left = node[i_left];            
            }
        }
        if(temp != NULL) {
            if(i_right < ARRAY_SIZE) {
                temp->right = node[i_right];   
            }
        }

    }

    printf("result: %d\n", widthOfBinaryTree(root));

}

