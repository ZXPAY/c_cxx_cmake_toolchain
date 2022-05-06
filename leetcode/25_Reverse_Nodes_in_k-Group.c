#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *generate_node(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->val = val;

    return node;
}

void print_node(struct ListNode *node) {
    while(node != NULL) {
        printf("%d,", node->val);
        node = node->next;
    }
    printf("\n");
}

struct ListNode *reverseKGroup(struct ListNode *head, int k) {
    /* Save the k node pointer */
    struct ListNode **buf_node_p = malloc(k*sizeof(struct ListNode *));
    struct ListNode *new_head = NULL;
    struct ListNode *temp = head;

    int cnt = 0;
    while(temp != NULL) {
        cnt++;
        if(cnt == k) {
            new_head = temp;
        }
        temp = temp->next;
    }
    if(new_head == NULL) return head;

    struct ListNode *last_k_node = NULL;
    temp = head;
    cnt = 0;
    while(temp != NULL) {
        buf_node_p[cnt++] = temp;

        if(cnt == k) {
            struct ListNode *k_next = temp->next;
            for(int i=k-1;i>=1;i--) {
                buf_node_p[i]->next = buf_node_p[i-1];
            }
            cnt = 0;
            if(last_k_node != NULL) {
                last_k_node->next = buf_node_p[k-1];
            }
            buf_node_p[0]->next = k_next;
            last_k_node = buf_node_p[0];
            temp = buf_node_p[0];
            // print_node(new_head);
        }
        temp = temp->next;
    }

    return new_head;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    struct ListNode *root = generate_node(1);

    root->next = generate_node(2);
    root->next->next = generate_node(3);
    root->next->next->next = generate_node(4);
    root->next->next->next->next = generate_node(5);


    struct ListNode *result = reverseKGroup(root, 3);

    struct ListNode *temp = result;
    while(temp != NULL) {
        printf("%d,", temp->val);
        temp = temp->next;
    }
    printf("\n");

}

