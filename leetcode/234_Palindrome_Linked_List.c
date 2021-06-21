#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Given the head of a singly linked list, return true if it is a palindrome.
*/



struct ListNode {
    int val;
    struct ListNode *next;
};


bool isPalindrome(struct ListNode* head) {
    int cnt = 0;
    struct ListNode *ptr = head;
    while(ptr != NULL) {
        ptr = ptr->next;
        cnt++;
    }

    int half_cnt = (cnt >> 1);

    // Do reverse first half
    struct ListNode *current = head;
    struct ListNode *next = NULL;
    struct ListNode *prev = NULL;
    for(int i=0;i<half_cnt;i++) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    if(cnt & 1) {
        current = current->next;
    }

    ptr = prev;
    for(int i=0;i<half_cnt;i++) {
        printf("%d, %d\n", ptr->val, current->val);
        if(ptr->val != current->val) {
            return false;
        }
        ptr = ptr->next;
        current = current->next;
    }

    return true;
}


int main(void) {
    printf("start \n");

    struct ListNode test_head = {
        .next = NULL,
        .val = 1
    };
    struct ListNode test_node1 = {
        .next = NULL,
        .val = 2
    };
    struct ListNode test_node2 = {
        .next = NULL,
        .val = 3
    };
    struct ListNode test_node3 = {
        .next = NULL,
        .val = 4
    };
    struct ListNode test_node4= {
        .next = NULL,
        .val = 5
    };
    struct ListNode test_node5 = {
        .next = NULL,
        .val = 6
    };
    struct ListNode test_node6 = {
        .next = NULL,
        .val = 7
    };


    test_head.next = &test_node1;
    test_node1.next = &test_node2;
    test_node2.next = &test_node3;
    test_node3.next = &test_node4;
    test_node4.next = &test_node5;
    test_node5.next = &test_node6;

    printf("isPalindrome: %d\n", isPalindrome(&test_head));


    return 0;
}

