#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


char *test_string[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
// char *test_string[] = {"eat", "tea"};

/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
*/

#define MAGIC_NUM     31
#define MODULE_NUM    1000007
long GLOBAL_ORDER[26];

typedef struct _linklist_t {
    struct _linklist_t *next;
    char *string_val;
    long hash_value;
} linklist_t;

linklist_t *generate_node(void) {
    linklist_t *node = (linklist_t *)malloc(sizeof(linklist_t));
    memset(node, 0, sizeof(linklist_t));

    return node;
}

long mod(long n, long m) {
    return (n % m + m) % m;
}

long hash(char *charater, int length) {
    long hash_value = 0;
    for(int i=0;i<length;i++) {
        assert((charater[i]-'a') < 26);
        hash_value += GLOBAL_ORDER[charater[i]-'a'] * charater[i];
        hash_value = mod(hash_value, MODULE_NUM);
    }
    return hash_value;
}

void add_to_hashmap(linklist_t **map, int map_len, long hash_value, char *str_val) {
    int index = mod(hash_value, map_len);
    
    linklist_t *node = generate_node();
    node->string_val = str_val;
    node->hash_value = hash_value;

    if(map[index] == NULL) {
        // first time
        map[index] = node;
        return;
    }

    int cnt = 0;
    while(map[index]->hash_value != hash_value) {
        if(++index >= map_len) index = 0;
        if(++cnt >= map_len) assert(0);
        if(map[index] == NULL) break;
    }

    if(map[index] == NULL) {
        // first time
        map[index] = node;
        return;
    }


    linklist_t *temp = map[index];
    linklist_t *last = temp;
    while(temp != NULL) {
        last = temp;
        temp = temp->next;
    }
    last->next = node;
}

bool search_hash_valid(linklist_t **map, int map_len, long hash_value) {
    int index = mod(hash_value, map_len);

    if(map[index] == NULL) return false;

    int cnt = 0;
    while(map[index]->hash_value != hash_value) {
        if(++index >= map_len) index = 0;
        if(++cnt >= map_len) assert(0);
        if(map[index] == NULL) return false;
    }
    return true;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes) {
    if(strs == NULL || strsSize == 0) return NULL;
    for(int i=0;i<26;i++) {
        if(i == 0)
            GLOBAL_ORDER[i] = 1;
        else
            GLOBAL_ORDER[i] = GLOBAL_ORDER[i-1]*31;
    
        GLOBAL_ORDER[i] = mod(GLOBAL_ORDER[i], MODULE_NUM);
    }

    char ***result = (char ***)malloc(strsSize * sizeof(char *));
    memset(result, 0, sizeof(char *));
    
    int *retcolsizes = malloc(strsSize * sizeof(int));
    *returnColumnSizes = retcolsizes;

    linklist_t **map = (linklist_t **)malloc(sizeof(linklist_t **) * strsSize*2);
    memset(map, 0, sizeof(linklist_t **)*strsSize*2);
    int map_len = strsSize * 2;

    for(int i=0;i<strsSize;i++) {
        long hash_value = hash(strs[i], strlen(strs[i]));
        add_to_hashmap(map, map_len, hash_value, strs[i]);
    }

    /* convert to result */
    int count = 0;
    for(int i=0;i<map_len;i++) {
        if(map[i] != NULL) {
            linklist_t *temp = map[i];
            int column_size = 0;
            result[count] = malloc(strsSize * sizeof(char *));
            while(temp != NULL) {
                result[count][column_size] = temp->string_val;
                column_size++;
                temp = temp->next;
            }
            retcolsizes[count] = column_size;
            count++;
        }
    }
    *returnSize = count;

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    char **str = test_string;
    int str_array_size = sizeof(test_string) / sizeof(*test_string);
    int return_size;
    int **return_columnSize = (int **)malloc(sizeof(int **));
    char ***ans = groupAnagrams(str, str_array_size, &return_size, return_columnSize);

    printf("return size: %d\n", return_size);

    for(int i=0;i<return_size;i++) {
        printf("==============\n");
        for(int j=0;j<*(*return_columnSize+i);j++) {
            printf("[%d, %d]\n", i, j);
            printf("%s\n", ans[i][j]);
        }
    }


}

