#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_arr1[] = {1, 4, 5};
int test_arr2[] = {1, 3, 4};
int test_arr3[] = {2, 6};

int *test_arr[] = {test_arr1, test_arr2, test_arr3};
#define ARRARY_LENGTH 3
int col_size[] = {3, 3, 2};


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


struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
    struct ListNode *result = NULL;
    struct ListNode *temp = NULL;
    bool first_flag = true;

    int val_min = INT32_MAX;
    int i = 0;
    struct ListNode **min_node = NULL;

    while(true) {
        if(i == listsSize) {
            if(min_node == NULL) {
                // Not found break
                break;
            }
            else {
                *min_node = (*min_node)->next;
            }
            printf("min: %d\n", val_min);
            if(first_flag) {
                result = generate_node(val_min);
                temp = result;
                first_flag = false;
            }
            else {
                temp->next = generate_node(val_min);
                temp = temp->next;
            }
            i = 0;
            val_min = INT32_MAX;
            min_node = NULL;
        }
        if(lists[i] != NULL) {
            if(lists[i]->val < val_min) {
                min_node = &lists[i];
                val_min = lists[i]->val;
            }
        }
        i++;
    }

    return result;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct ListNode **root = malloc(sizeof(struct ListNode *));

    for(int i=0;i<ARRARY_LENGTH;i++) {
        root[i] = generate_node(test_arr[i][0]);
        struct ListNode *temp = root[i];
        for(int j=1;j<col_size[i];j++) {
            temp->next = generate_node(test_arr[i][j]);
            temp = temp->next;
        }
    }

    struct ListNode *result = mergeKLists(root, ARRARY_LENGTH);
    printf("========= Result ==========\n");
    while(result != NULL) {
        printf("%d, ", result->val);
        result = result->next;
    }
    printf("\n");


}

