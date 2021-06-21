#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
Given the head of a linked list and an integer val, 
remove all the nodes of the linked list that has Node.val == val, and return the new head.
*/


struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode *removeElements(struct ListNode *head, int val) {
    if(head == NULL) return NULL;
    int cnt = 0;
    struct ListNode *ptr = head;
    while(ptr != NULL) {
        cnt++;
        if(ptr->val == val) {
            cnt--;
        }
        ptr = ptr->next;
    }
    if(cnt == 0) {
        return NULL;
    }
    struct ListNode *new_head = (struct ListNode *) malloc(cnt*sizeof(struct ListNode));
    memset(new_head, 0, cnt*sizeof(struct ListNode));
    for(int i=0;i<cnt-1;i++) {
        new_head[i].next = &new_head[i+1];
    }
    
    ptr = head;
    struct ListNode *new_ptr = new_head;

    while(ptr!=NULL) {
        // printf("%d\n", ptr->val);
        if(ptr->val != val) {
            new_ptr->val = ptr->val;
            new_ptr = new_ptr->next;
        }
        if(ptr->next == NULL) {
            return new_head;
        }
        ptr = ptr->next;
    }
    return new_head;
}


int main() {
    printf("start\n");

    struct ListNode head = {
        .next = NULL,
        .val = 7
    };
    struct ListNode node1 = {
        .next = NULL,
        .val = 7
    };
    struct ListNode node2 = {
        .next = NULL,
        .val = 7
    };
    struct ListNode node3 = {
        .next = NULL,
        .val = 7
    };
    struct ListNode node4 = {
        .next = NULL,
        .val = 4
    };
    struct ListNode node5 = {
        .next = NULL,
        .val = 5
    };
    struct ListNode node6 = {
        .next = NULL,
        .val = 6
    };

    head.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;

    printf("linklist value: \n");
    struct ListNode *ptr = &head;
    while(ptr != NULL) {
        printf("%d, ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
    printf("remove linklist value 6\n");
    
    ptr = removeElements(&head, 7);
    while(ptr != NULL) {
        printf("%d, ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}
