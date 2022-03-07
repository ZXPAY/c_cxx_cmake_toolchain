#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {1, 2, 2, 1};
int test_array[] = {1, 2};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

void isPalindrome_help(struct ListNode **node_st, struct ListNode *node, bool *result) {
    if(node == NULL) return ;

    isPalindrome_help(node_st, node->next, result);

    // printf("%p, %p\n", *node_st, node);

    if((*node_st)->val != node->val) *result = false;

    *node_st = (*node_st)->next;
}

bool isPalindrome(struct ListNode *head) {
    struct ListNode *node_st = head;
    bool result = true;

    isPalindrome_help(&node_st, head, &result);

    return result;
}

int main(int argc, char *argv[]) {
    struct ListNode *head;
    struct ListNode *temp_node;
    for(int i=0;i<ARRAY_SIZE;i++) {
        struct ListNode *temp = malloc(sizeof(struct ListNode));
        temp->val = test_array[i];

        if(i == 0) {
            head = temp;
            temp_node = temp;
        }
        else {
            temp_node->next = temp;
            temp_node = temp;
        }
        printf("%p: %d\n", temp_node, temp_node->val);
        
    }
    
    printf("isPalindrome: %d\n", isPalindrome(head));

}

