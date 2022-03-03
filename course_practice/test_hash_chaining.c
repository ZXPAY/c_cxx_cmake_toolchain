#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


/* Handle collision */
typedef struct _linklist_t {
    struct _linklist_t *next;
    int val;
} linklist_t;


int test_array[] = {108, 106, 100, 103, 117, 111, 115, 124, 129, 339, 10, 20};
// int test_array[] = {12, 102};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

linklist_t *generate_node(void) {
    linklist_t *node = (linklist_t *)malloc(sizeof(linklist_t));
    memset(node, 0, sizeof(linklist_t));

    return node;
}

linklist_t **build_mod_hash(int *arr, int arr_size) {
    linklist_t **map = (linklist_t **)malloc(sizeof(linklist_t **) * arr_size);
    memset(map, 0, sizeof(linklist_t **)*arr_size);
    for(int i=0;i<arr_size;i++) {
        *(map+i) = NULL;
    }


    // Build hash map
    for(int i=0;i<arr_size;i++) {
        int hash_index = arr[i] % 10;
        // map[hash_index] = arr[i];
        printf("hash: %d\n", hash_index);
        linklist_t *temp = map[hash_index];
        if(temp == NULL) {
            // first time
            temp = generate_node();
            temp->val = arr[i];
            map[hash_index] = temp;
            continue;
        }
        linklist_t *last = temp;
        for(;temp!=NULL;temp=temp->next) {
            last = temp;
        }

        temp = generate_node();
        temp->val = arr[i];
        last->next = temp;

    }

    return map;
}

bool search(linklist_t **map, int target) {
    // if(map[target%10] == target) return true;
    for(linklist_t *a=map[target%10];a!=NULL;a=a->next) {
        if(a->val == target) return true;
    }

    return false;
}

int main() {

    linklist_t **map = build_mod_hash(test_array, ARRAY_SIZE);

    printf("print out\n");
    for(int i=0;i<ARRAY_SIZE;i++) {
        for(linklist_t *temp=map[i];temp!=NULL;temp=temp->next) {
            printf("[%d]: %d\n", i, temp->val);
        }
    }

    printf("Start search\n");
    for(int i=0;i<ARRAY_SIZE;i++) {
        // printf("=> %d\n", map[i]);
        if(search(map, test_array[i])) {
            printf("Found: %d\n", test_array[i]);
        }
        else {
            printf("Not found\n");
        }
    }


    return 0;
}

