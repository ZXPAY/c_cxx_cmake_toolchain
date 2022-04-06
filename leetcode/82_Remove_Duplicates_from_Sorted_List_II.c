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

struct ListNode *deleteDuplicates(struct ListNode *head) {
    if(head == NULL) return NULL;
    struct ListNode *temp = head;

    int count = 0;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    int *arr = malloc((count+1)*sizeof(int));
    memset(arr, 0, (count+1)*sizeof(int));
    int i_arr = 0;

    temp = head;
    arr[i_arr++] = temp->val;
    int prev_val = temp->val;
    temp = temp->next;
    
    while(temp != NULL) {
        arr[i_arr] = temp->val;
        if(arr[i_arr] == prev_val) {
            arr[i_arr-1] = INT32_MIN;
            arr[i_arr] = INT32_MIN;
        }
        i_arr++;
        prev_val = temp->val;
        temp = temp->next;
    }

    for(int i=0;i<count;i++) {
        printf("%d\n", arr[i]);
    }

    // update head
    i_arr = 0;
    while(arr[i_arr++] == INT32_MIN) {
        struct ListNode *old = head;
        head = head->next;
        free(old);
    }
    if(head == NULL) return NULL;
    // update node
    temp = head->next;
    struct ListNode *prev = head;
    struct ListNode *delete_node = NULL;
    for(int i=i_arr;i<count;i++) {
        if(arr[i] != INT32_MIN) {
            prev->next = temp;
            prev = prev->next;
        }
        else {
            delete_node = temp;
        }
        temp = temp->next;
        if(delete_node != NULL) {
            free(delete_node);
            delete_node = NULL;
        }
    }
    prev->next = NULL;

    return head;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct ListNode *root = generate_node(1);
    struct ListNode *temp = generate_node(1);
    root->next = temp;
    
    // temp->next = generate_node(3);
    // temp = temp->next;
    // temp->next = generate_node(4);
    // temp = temp->next;
    // temp->next = generate_node(5);
    // temp = temp->next;
    // temp->next = generate_node(6);
    // temp = temp->next;
    // temp->next = generate_node(7);
    // temp = temp->next;
    // temp->next = generate_node(7);
    // temp = temp->next;

    struct ListNode *result = deleteDuplicates(root);
    while(result != NULL) {
        printf("%d, ", result->val);
        result = result->next;
    }
    printf("\n");


}

