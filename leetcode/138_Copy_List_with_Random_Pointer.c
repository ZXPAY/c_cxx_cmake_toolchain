#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define ROW 5
#define COL 2
int test_node[ROW][COL] = {
    {7,-1},
    {13,0},
    {11,4},
    {10,2},
    {1,0}};

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */
struct Node *generate_node(int val) {
    struct Node *node = malloc(sizeof(struct Node));
    memset(node, 0, sizeof(struct Node));
    node->val = val;

    return node;
}

#define HASH_SIZE   (1200)

typedef struct _myhash_t {
    size_t old_addr;
    size_t new_addr;
} myhash_t;

void add_to_hash(myhash_t *map, size_t old_addr, size_t new_addr) {
    // Using open addressing to collect map
    int index = old_addr % HASH_SIZE;
    int cnt = 0;
    while(map[index].old_addr != 0) {
        index++;
        if(index == HASH_SIZE) index = 0;
        if(++cnt > HASH_SIZE) return;
    }
    map[index].old_addr = old_addr;
    map[index].new_addr = new_addr;
}

size_t search_hash(myhash_t *map, size_t old_addr) {
    // Using open addressing to search
    int index = old_addr % HASH_SIZE;
    int cnt = 0;
    while(map[index].old_addr != old_addr) {
        index++;
        if(index == HASH_SIZE) index = 0;
        if(++cnt > HASH_SIZE) return;
    }
    
    return map[index].new_addr;
}

struct Node *copyRandomList_by_hashmap(struct Node *head) {
    if(head == NULL) return NULL;
    struct Node *copy_head = generate_node(head->val);
    struct Node *temp = copy_head;
    struct Node *old_temp = head->next;

    myhash_t *map = malloc(sizeof(myhash_t)*HASH_SIZE);
    memset(map, 0, sizeof(myhash_t)*HASH_SIZE);

    add_to_hash(map, (size_t)head, copy_head);
    
    while(old_temp!=NULL) {
        temp->next = generate_node(old_temp->val);
        temp = temp->next;
        add_to_hash(map, (size_t)old_temp, (size_t)temp);
        printf("%x,%x\n", (size_t)old_temp, (size_t)temp);
        old_temp = old_temp->next;
    }

    // pointer to random
    temp = copy_head;
    old_temp = head;

    while(old_temp != NULL) {
        if(old_temp->random == NULL) temp->random = NULL;
        else {
            temp->random = search_hash(map, old_temp->random);
        }

        old_temp = old_temp->next;
        temp = temp->next;
    }


    return copy_head;
}

struct Node *copyRandomList(struct Node *head) {
    if(head == NULL) return NULL;
    struct Node *copy_head = generate_node(head->val);
    struct Node *temp = copy_head;
    struct Node *old_temp = head->next;
    
    while(old_temp!=NULL) {
        temp->next = generate_node(old_temp->val);
        temp = temp->next;
        old_temp = old_temp->next;
    }

    // pointer to random
    temp = copy_head;
    old_temp = head;

    while(old_temp != NULL) {
        if(old_temp->random == NULL) temp->random = NULL;
        else {
            struct Node *find_node_old = head;
            struct Node *find_node_new = copy_head;
            // Linear search
            while(find_node_old != old_temp->random && find_node_old != NULL) {
                find_node_old = find_node_old->next;
                find_node_new = find_node_new->next;
            }
            temp->random = find_node_new;
        }

        old_temp = old_temp->next;
        temp = temp->next;
    }


    return copy_head;
}

int main(int argc, char *argv[]) {
    struct Node *head = generate_node(test_node[0][0]);
    struct Node *temp = head;
    
    printf("head: %p\n", head);
    for(int i=1;i<ROW;i++) {
        temp->next = generate_node(test_node[i][0]);
        temp = temp->next;
        printf("%p\n", temp);
    }

    // pointer to random
    int j = 0;
    temp = head;
    while(j<ROW) {
        if(test_node[j][1] == -1) {
            temp->random = NULL;
        }
        else {
            struct Node *find_node = head;
            for(int k=0;k<test_node[j][1];k++) {
                // index
                find_node = find_node->next;
            }
            temp->random = find_node;   
        }
        j++;
        temp = temp->next;
    }

    // print the result
    temp = head;
    while(temp != NULL) {
        printf("node, next, random, %p, %p, %p\n", temp, temp->next, temp->random);

        temp = temp->next;
    }

    printf("Deep copy\n");
    struct Node *deep_copy_node = copyRandomList(head);
    temp = deep_copy_node;
    while(temp != NULL) {
        printf("node, next, random, %p, %p, %p\n", temp, temp->next, temp->random);

        temp = temp->next;
    }

    printf("Deep copy by hash\n");
    struct Node *deep_copy_node2 = copyRandomList_by_hashmap(head);
    temp = deep_copy_node2;
    while(temp != NULL) {
        printf("node, next, random, %p, %p, %p\n", temp, temp->next, temp->random);

        temp = temp->next;
    }

}

