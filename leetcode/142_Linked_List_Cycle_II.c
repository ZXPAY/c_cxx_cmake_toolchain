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
    node->val = val;
    node->next = NULL;

    return node;
}

#define HASH_SIZE   (1200)
void add_to_hash(size_t *map, size_t addr) {
    // Using open addressing to collect map
    int index = addr % HASH_SIZE;
    int cnt = 0;
    while(map[index] != 0) {
        index++;
        if(index == HASH_SIZE) index = 0;
        if(++cnt > HASH_SIZE) return;
    }
    map[index] = addr;
}

bool search_hash(size_t *map, size_t addr) {
    // Using open addressing to search
    int index = addr % HASH_SIZE;
    int cnt = 0;
    if(map[index] == 0) return false;
    while(map[index] != addr) {
        index++;
        if(index == HASH_SIZE) index = 0;
        if(++cnt > HASH_SIZE) return false;
    }
    return true;
}

struct ListNode *detectCycle2(struct ListNode *head) {
    size_t *hash_map = (size_t *)malloc(sizeof(size_t)*HASH_SIZE);
    struct ListNode *temp = head;
    
    while(temp != NULL) {
        if(search_hash(hash_map, (size_t)temp->next)) {
            return temp->next;
        }
        add_to_hash(hash_map, (size_t)temp);
        temp = temp->next;
    }

    return NULL;
}

struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!(fast && fast->next)) return NULL;
    while (head != slow) {
        head = head->next;
        slow = slow->next;
    }
    return head;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    struct ListNode *root = generate_node(3);
    struct ListNode *temp = root;
    struct ListNode *cycle;
    
    temp->next = generate_node(2);
    temp = temp->next;
    cycle = temp;

    temp->next = generate_node(0);
    temp = temp->next;

    temp->next = generate_node(-4);
    temp = temp->next;

    temp->next = cycle;

    printf("cycle: %p\n", cycle);

    struct ListNode *node = detectCycle(root);
    printf("result: %p\n", node);

}

