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
char test_string[] = "dcab";
int test_pairs[][2] = {{0, 3}, {1, 2}, {0, 2}};

#define PAIRS_LEN   (sizeof(test_pairs) / sizeof(test_pairs[0]))


int find_root(int *parent, int a) {
    if (a == parent[a])
        return a;
    return parent[a] = find_root(parentparent[a]);
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

char *smallestStringWithSwaps(char *s, int **pairs, int pairsSize, int *pairsColSize){
    int length = strlen(s) + 1;
    int *parent = malloc(length*sizeof(int));
    memset(parent, 0, length*sizeof(int));

    for(int i=0;i<length;i++) {
        parent[i] = i;
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

