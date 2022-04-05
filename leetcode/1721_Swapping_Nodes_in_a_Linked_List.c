#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
*/

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

struct ListNode *generate_node(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;

    return node;
}

struct ListNode* swapNodes(struct ListNode* head, int k){
    // Find first
    struct ListNode *first = NULL;
    int cnt = 1;

    struct ListNode *temp = head;
    while(temp != NULL) {
        if(cnt == k) {
            first = temp;
        }
        cnt++;
        temp = temp->next;
    }

    // Find second
    struct ListNode *second = NULL;
    temp = first;
    int cnt2 = k;
    int cnt3 = cnt - k;
    printf("%d, %d, %d\n", cnt2, cnt3, temp->val);
    if(cnt3 < cnt2) {
        cnt2 = 1;
        temp = head;
    }
    while(temp != NULL) {
        printf("%p, %d, %d, %d\n", temp, cnt2, cnt3, temp->val);
        if(cnt2 == cnt3) {
            second = temp;
            break;
        }
        cnt2++;
        temp = temp->next;
    }
    int temp_int = first->val;
    first->val = second->val;
    second->val = temp_int;

    return head;
}

struct ListNode* swapNodes2(struct ListNode* head, int k){
    if(k < 1) return NULL;
    struct ListNode *temp = head;
    int node_len = 0;
    while(temp != NULL) {
        node_len++;
        
        temp = temp->next;
    }
    
    
    struct ListNode **node_arr = malloc(node_len*sizeof(struct ListNode *));
    temp = head;
    int cnt = 0;
    while(temp != NULL) {
        node_arr[cnt++] = temp;
        
        temp = temp->next;
    }
    
    // swap
    struct ListNode *temp_node = node_arr[k-1];
    node_arr[k-1] = node_arr[node_len-k];
    node_arr[node_len-k] = temp_node;
    
    // rebuild the node list
    struct ListNode *new_head = node_arr[0];
    temp_node = new_head;
    for(int i=1;i<node_len;i++) {
        temp_node->next = node_arr[i];
        temp_node = temp_node->next;
    }
    temp_node->next = NULL;
    
    
    return new_head;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct ListNode *root = generate_node(1);
    struct ListNode *temp = root;

    temp->next = generate_node(2);
    temp = temp->next;
    temp->next = generate_node(3);
    temp = temp->next;
    temp->next = generate_node(4);
    temp = temp->next;
    temp->next = generate_node(5);
    temp = temp->next;
    temp->next = generate_node(6);
    temp = temp->next;
    temp->next = generate_node(7);
    temp = temp->next;
    temp->next = generate_node(8);
    temp = temp->next;
    temp->next = generate_node(9);
    temp = temp->next;



    temp = swapNodes(root, 8);

    while(temp!=NULL) {
        printf("%d, ", temp->val);
        temp = temp->next;
    }
    printf("\n");




}

