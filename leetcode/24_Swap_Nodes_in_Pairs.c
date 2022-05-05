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

struct ListNode *swapPairs(struct ListNode *head) {
    if(head == NULL) return NULL;
    if(head->next == NULL) return head;

    struct ListNode *prev_node = head;
    struct ListNode *cur_node = head->next;
    struct ListNode *result = head->next;

    struct ListNode *next_cur = NULL;
    struct ListNode *next_prev = NULL;
    while(cur_node != NULL) {
        // printf("%d->%d\n", prev_node->val, cur_node->val);
        struct ListNode *temp = NULL;
        if(cur_node->next != NULL) {
            temp = cur_node->next->next;
        }
        next_prev = cur_node->next;
        next_cur = temp;
        
        /* 1->2->3->4    ==>  2->1->4  3->4 */
        /* 2->1->4  3->4 ==>  2->1->4->3    */
        cur_node->next = prev_node;
        prev_node->next = temp;
        
        if(next_cur == NULL) {
            /* Last node */
            if(next_prev != NULL) {
                /* nodes are odd */
                prev_node->next = next_prev;
            }
        }
        /* update next two node */
        cur_node = next_cur;
        prev_node = next_prev;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    struct ListNode *root = generate_node(1);

    root->next = generate_node(2);
    root->next->next = generate_node(3);
    root->next->next->next = generate_node(4);


    struct ListNode *result = swapPairs(root);

    struct ListNode *temp = result;
    while(temp != NULL) {
        printf("%d,", temp->val);
        temp = temp->next;
    }
    printf("\n");

}

