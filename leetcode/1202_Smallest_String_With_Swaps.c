#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* ans: bacd */
// char test_string[] = "dcab";
// int test_pairs[][2] = {{0, 3}, {1, 2}};

/* ans: abcd */
// char test_string[] = "dcab";
// int test_pairs[][2] = {{0, 3}, {1, 2}, {0, 2}};

/* ans: lpqqmwm */
char test_string[] = "pwqlmqm";
int test_pairs[][2] = {{5,3},{3,0},{5,1},{1,1},{1,5},{3,0},{0,2}};

#define PAIRS_LEN   (sizeof(test_pairs) / sizeof(test_pairs[0]))

/* find the root (or head) in set */
int find(int *parent, int a) {
    if (a != parent[a])
        parent[a] = find(parent, parent[a]);
    return parent[a];
}

/* union a and b, a value to b */
void make_union(int *parent, int a, int b) {
    parent[find(parent, a)] = find(parent, b);
}

typedef struct {
    int char_cnt[26];
} save_char_t;

char *smallestStringWithSwaps(char *s, int **pairs, int pairsSize, int *pairsColSize){
    int length = strlen(s);
    int *parent = malloc(length*sizeof(int));
    memset(parent, 0, length*sizeof(int));

    save_char_t **save_char_buf = malloc(length*sizeof(save_char_t *));
    for(int i=0;i<length;i++) save_char_buf[i] = NULL;

    // Initialize the parent
    for(int i=0;i<length;i++) {
        parent[i] = i;
    }

    /* Build the multi-set */
    for(int i=0;i<pairsSize;i++) {
        make_union(parent, pairs[i][0], pairs[i][1]);
    }

    /* Print the multi-set */
    for(int i=0;i<length;i++) {
        printf("%d, ", find(parent, i));
    }
    printf("\n");

    /* Sorting in each set */
    // Collect the characters information to save_char_buf
    for(int i=0;i<length;i++) {
        int i_root = find(parent, i);
        if(save_char_buf[i_root] == NULL) {
            save_char_buf[i_root] = malloc(sizeof(save_char_t));
            memset(save_char_buf[i_root], 0, sizeof(save_char_t));
        }
        save_char_buf[i_root]->char_cnt[s[i]-'a']++;
    }
    int i_cnt = 0;
    int cur_root = find(parent, 0);
    // Put characters to s[i] orderly
    for(int i=0;i<length;i++) {
        int i_root = find(parent, i);
        if(i_root != cur_root) {
            cur_root = i_root;
            i_cnt = 0;
        }
        while(save_char_buf[i_root]->char_cnt[i_cnt] == 0) i_cnt++;
        s[i] = i_cnt + 'a';
        save_char_buf[i_root]->char_cnt[i_cnt]--;
        if(save_char_buf[i_root]->char_cnt[i_cnt] == 0) i_cnt = 0;
    }

    free(parent);
    for(int i=0;i<length;i++) {
        if(save_char_buf[i] != NULL) free(save_char_buf[i]);
    }
    return s;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **pairs = malloc(PAIRS_LEN*sizeof(int));

    for(int i=0;i<PAIRS_LEN;i++) {
        pairs[i] = malloc(2*sizeof(int));
        memcpy(pairs[i], &test_pairs[i][0], 2*sizeof(int));
    }

    int pair_col = 2;
    printf("raw: %s\n", test_string);
    char *result = smallestStringWithSwaps(test_string, pairs, PAIRS_LEN, &pair_col);
    printf("result: %s\n", result);


}

