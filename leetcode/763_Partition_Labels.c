#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_string[] = "ababcbacadefegdehijhklij";  // {9, 7, 8}
// char test_string[] = "caedbdedda"; // {1, 9}
// char test_string[] = "eaaaabaaec"; // {9, 1}
// char test_string[] = "vhaagbqkaq";    // {1, 1, 8}

/*
You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part.

Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.

Return a list of integers representing the size of these parts.
*/


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *partitionLabels(char *s, int *returnSize) {
    int length = strlen(s);
    int *char_map_index = malloc(26*sizeof(int));
    memset(char_map_index, 0xFF, 26*sizeof(int));


    int *labels = malloc(length*sizeof(int));
    memset(labels, 0 ,length*sizeof(int));
    *returnSize = 0;

    // collect the a~z last index
    for(int i=0;i<length;i++) {
        char_map_index[s[i]-'a'] = i;
    }

    /* Debug print */
    for(int i=0;i<26;i++) {
        if(char_map_index[i] != -1) {
            printf("[%c]: %d\n", i+'a', char_map_index[i]);
        }
    }

    int temp_max = 0;
    int cnt = 0;
    for(int i=0;i<length;i++) {
        cnt++;
        if(char_map_index[s[i]-'a'] > temp_max) {
            temp_max = char_map_index[s[i]-'a'];
        }
        if(i == temp_max) {
            labels[(*returnSize)++] = cnt;
            cnt = 0;
        }
    }
    if(cnt != 0) labels[(*returnSize)++] = cnt;

    return labels;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_size = 0;
    int *labels = partitionLabels(test_string, &return_size);
    
    printf("{");
    for(int i=0;i<return_size;i++) {
        printf("%d, ", labels[i]);
    }
    printf("}\n");

}

