#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define VALUE_NOTUSE INT32_MIN

typedef struct _map_para_t {
    int count;
    int value;
} map_para_t;

typedef struct _stack_dblinklist_t {
    int val;
    struct _stack_dblinklist_t *next;
    struct _stack_dblinklist_t *prev;
} stack_dblinklist_t;

typedef struct {
    stack_dblinklist_t *head;
    stack_dblinklist_t *tail;
    stack_dblinklist_t *max_node;
    int max_count;
    int max_value;
    map_para_t *hash_map;
    int map_length;
    int map_count;
    int top_flag;
} FreqStack;


int mod(int n, int m) {
    return (n % m + m) % m;
}

void insert_hash(map_para_t *map, int value, int hash_size, FreqStack *freq_stack) {
    int hash_index = mod(value, hash_size);

    int count = 0;
    while(count++ < hash_size) {
        if(map[hash_index].count == 0) {
            map[hash_index].value = value;
            map[hash_index].count++;

            break;
        }
        else if(map[hash_index].value == value) {
            map[hash_index].count++;
        
            break;
        }
        else {
            hash_index++;
            if(hash_index == hash_size) hash_index = 0;
        }
    }

}

void search(map_para_t *map, int target, int hash_size, map_para_t **found_map) {
    int hash_index = mod(target, hash_size);
    int count = 0;
    while(count++ < hash_size) {
        if(map[hash_index].value == target) {
            *found_map = &map[hash_index];
            return;
        }
        if(map[hash_index].value == VALUE_NOTUSE) return;

        hash_index++;
        if(hash_index == hash_size) hash_index = 0;
    }
}


stack_dblinklist_t *create_node(int value) {
    stack_dblinklist_t *node = malloc(sizeof(stack_dblinklist_t));
    node->next = NULL;
    node->prev = NULL;
    node->val = value;

    return node;
}

FreqStack* freqStackCreate() {
    FreqStack *freq_stack = malloc(sizeof(FreqStack));    
    memset(freq_stack, 0, sizeof(FreqStack));

    map_para_t *map = malloc(sizeof(map_para_t)*1000);
    memset(map, 0, 1000*sizeof(map_para_t));
    freq_stack->hash_map = map;
    freq_stack->map_length = 1000;

    return freq_stack;
}

void freqStackPush(FreqStack *obj, int val) {
    stack_dblinklist_t *node = create_node(val);

    if(obj->head == NULL) {
        obj->head = node;
        obj->tail = node;
    }
    else {
        if(obj->head == obj->tail) {
            obj->head->next = node;
            node->prev = obj->head;

            // update the tail
            obj->tail = node;
        }
        else {
            obj->tail->next = node;
            node->prev = obj->tail;

            // update the tail
            obj->tail = node;
        }
    }

    // push the node count to hash map by using open addressing
    insert_hash(obj->hash_map, val, obj->map_length, obj);

    obj->map_count++;
    if(obj->map_count > obj->map_length) {
        obj->hash_map = realloc(obj->hash_map, obj->map_length*2);
        obj->map_length *= 2;
    }

    obj->max_count = get_max_count(obj);
}

int get_max_count(FreqStack *obj) {
    stack_dblinklist_t *temp_node = obj->head;
    int max_count = 0;
    // find max count
    while(temp_node != NULL) {
        map_para_t *temp_para = NULL;

        search(obj->hash_map, temp_node->val, obj->map_length, &temp_para);
        
        if(max_count < temp_para->count) max_count = temp_para->count;

        temp_node = temp_node->next;
    }
    
    return max_count;
}

int freqStackPop(FreqStack *obj) {
    if(obj->map_count == 0) return -1;
    // printf("max count: %d\n", obj->max_count);

    stack_dblinklist_t *temp_node = obj->head;
    stack_dblinklist_t *max_node = obj->head;
    int max_value = temp_node->val;
    map_para_t *max_map_ptr = NULL;

    // find max count
    int cnt = 0;
    while(temp_node != NULL) {
        map_para_t *temp_para = NULL;
        search(obj->hash_map, temp_node->val, obj->map_length, &temp_para);
        // printf("%d, %d\n", temp_para->value, temp_para->count);

        assert(temp_para != NULL);
        if(temp_para->count == obj->max_count) {
            if(temp_para->value >= max_value) {
                max_value = temp_para->value;
                max_map_ptr = temp_para;
                max_node = temp_node;
            }
            else {
                max_value = temp_para->value;
                max_map_ptr = temp_para;
                max_node = temp_node;
            }
            cnt++;
        }

        temp_node = temp_node->next;
    }
    if(cnt == obj->map_count) {
        // use the tail
        // printf("tail\n");
        max_node = obj->tail;
        max_value = obj->tail->val;
    }

    // pop the node
    if(max_node->prev == NULL && max_node->next != NULL) {
        // head node
        // printf("case 0\n");
        obj->head = max_node->next;
        obj->head->prev = NULL;
    }
    else if(max_node->next == NULL && max_node->prev != NULL) {
        // tail node
        // printf("case 1\n");
        obj->tail = max_node->prev;
        obj->tail->next = NULL;
    }
    else if(max_node->prev != NULL && max_node->next != NULL) {
        // head ~ tail node
        // printf("case 2\n");
        max_node->prev->next = max_node->next;
        max_node->next->prev = max_node->prev;
    }
    else if(max_node->next == NULL && max_node->prev == NULL) {
        // Final
        // printf("case 3\n");
        obj->head = NULL;
    }
    free(max_node);
    max_map_ptr->count--;

    // update the max count
    obj->map_count--;
    obj->max_count = get_max_count(obj);
    printf("pop: %d\n", max_value);
    return max_value;
}


void freqStackFree(FreqStack *obj) {
    free(obj);
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    FreqStack *freq_stack = freqStackCreate();
    // freqStackPush(freq_stack, 5);
    // freqStackPush(freq_stack, 7);
    // freqStackPush(freq_stack, 5);
    // freqStackPush(freq_stack, 7);
    // freqStackPush(freq_stack, 4);
    // freqStackPush(freq_stack, 5);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);
    // freqStackPop(freq_stack);

    freqStackPush(freq_stack, 4);
    freqStackPush(freq_stack, 0);
    freqStackPush(freq_stack, 9);
    freqStackPush(freq_stack, 3);
    freqStackPush(freq_stack, 4);
    freqStackPush(freq_stack, 2);
    freqStackPop(freq_stack);
    freqStackPush(freq_stack, 6);
    freqStackPop(freq_stack);
    freqStackPush(freq_stack, 1);
    freqStackPop(freq_stack);
    freqStackPush(freq_stack, 1);
    freqStackPop(freq_stack);
    freqStackPush(freq_stack, 4);
    freqStackPop(freq_stack);
    freqStackPop(freq_stack);
    freqStackPop(freq_stack);
    freqStackPop(freq_stack);
    freqStackPop(freq_stack);
    freqStackPop(freq_stack);
}

