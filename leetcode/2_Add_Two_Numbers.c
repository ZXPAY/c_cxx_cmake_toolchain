#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

// int test_arr1[] = {2, 4, 3};
// int test_arr2[] = {5, 6, 4};
// ans: 7,0,8

int test_arr1[] = {9,9,9,9,9,9,9};
int test_arr2[] = {9,9,9,9};
// ans: 8,9,9,9,0,0,0,1

struct ListNode {
    int val;
    struct Listode *next;
};

#define MAX_DIGIT  100

struct ListNode *generate_node(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// post-order traversal
void getnum_help(struct ListNode *node, char *num_str, int *str_count) {
    if(node == NULL) return NULL;
    
    getnum_help(node->next, num_str, str_count);

    // post order
    num_str[(*str_count)++] = node->val + '0';
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    char *l1_num_str = malloc(sizeof(char)*MAX_DIGIT);
    char *l2_num_str = malloc(sizeof(char)*MAX_DIGIT);
    char *l3_num_str = malloc(sizeof(char)*(MAX_DIGIT+1));
    memset(l1_num_str, 0, sizeof(char)*MAX_DIGIT);
    memset(l2_num_str, 0, sizeof(char)*MAX_DIGIT);
    memset(l3_num_str, 0, sizeof(char)*(MAX_DIGIT+1));

    int l1_str_count = 0;
    int l2_str_count = 0;
    int l3_str_count = 0;

    getnum_help(l1, l1_num_str, &l1_str_count);
    getnum_help(l2, l2_num_str, &l2_str_count);

    // printf("l1[%d]: %s, l2[%d]: %s\n", l1_str_count, l1_num_str, l2_str_count, l2_num_str);


    /* char array summation to l3_num_str and build the struct ListNode */
    int carry = 0, temp;
    while(true) {
        if(l1_str_count <= 0 && l2_str_count <= 0) break;
        printf("%d, %d\n", l1_str_count-1, l2_str_count-1);
        
        if(l1_str_count > 0 && l2_str_count > 0) {
            temp = l1_num_str[l1_str_count-1] - '0' + l2_num_str[l2_str_count-1] - '0' + carry;
        }
        else if(l1_str_count > 0 && l2_str_count <= 0) {
            temp = l1_num_str[l1_str_count-1] - '0' + carry;
        }
        else if(l1_str_count <= 0 && l2_str_count > 0) {
            temp = l2_num_str[l2_str_count-1] - '0' + carry;
        }
        if(temp >= 10) {
            carry = 1;
            temp %= 10;
        }
        else {
            carry = 0;
        }
        l3_num_str[l3_str_count++] = temp + '0';

        l1_str_count--;
        l2_str_count--;
    }

    // printf("=> %s\n", l3_num_str);
    
    // Build the linklist
    struct ListNode *root = generate_node(l3_num_str[0]-'0');
    struct ListNode *temp_node = root;

    for(int i=1;i<l3_str_count;i++) {
        temp_node->next = generate_node(l3_num_str[i]-'0');
        temp_node = temp_node->next;
    }

    if(carry) {
        temp_node->next = generate_node(1);
    }

    return root;
}

int main(int argc, char *argv[]) {
    struct ListNode *l1_head = generate_node(test_arr1[0]);
    struct ListNode *l2_head = generate_node(test_arr2[0]);

    struct ListNode *temp_l1 = l1_head;
    struct ListNode *temp_l2 = l2_head;

    for(int i=1;i<sizeof(test_arr1) / sizeof(int);i++) {
        temp_l1->next = generate_node(test_arr1[i]);
        temp_l1 = temp_l1->next;
    }
    for(int i=1;i<sizeof(test_arr2) / sizeof(int);i++) {
        temp_l2->next = generate_node(test_arr2[i]);
        temp_l2 = temp_l2->next;
    }

    struct ListNode *node = addTwoNumbers(l1_head, l2_head);

    // print out the result
    while(node != NULL) {
        printf("%d, ", node->val);
        node = node->next;
    }
    printf("\n");
}

