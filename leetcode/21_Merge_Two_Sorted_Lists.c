#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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
    node->next = NULL;
    node->val = val;

    return node;
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
    if(list1 == NULL) return list2;
    else if(list2 == NULL) return list1;

    struct ListNode *list_merge = NULL;

    if(list1->val > list2->val) {
        list_merge = list2;
        list2 = list2->next;
    }
    else {
        list_merge = list1;
        list1 = list1->next;

    }

    struct ListNode *temp = list_merge;
    while(list1 != NULL || list2 != NULL) {
        if(list1 != NULL && list2 != NULL) {
            if(list1->val < list2->val) {
                temp->next = list1;
                list1 = list1->next;
                temp = temp->next;
            }
            else {
                temp->next = list2;
                list2 = list2->next;
                temp = temp->next;
            }
        }
        else if(list1 != NULL) {
            temp->next = list1;
            temp = temp->next;
            list1 = list1->next;
        }
        else if(list2 != NULL) {
            temp->next = list2;
            temp = temp->next;
            list2 = list2->next;
        }
    }

    return list_merge;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct ListNode *root1 = generate_node(1);
    struct ListNode *root2 = generate_node(1);

    root1->next = generate_node(2);
    root1->next->next = generate_node(4);

    root2->next = generate_node(3);
    root2->next->next = generate_node(4);

    struct ListNode *result = mergeTwoLists(root1, root2);

    struct ListNode *temp = result;
    while(temp != NULL) {
        printf("%d,", temp->val);
        temp = temp->next;
    }
    printf("\n");

}

