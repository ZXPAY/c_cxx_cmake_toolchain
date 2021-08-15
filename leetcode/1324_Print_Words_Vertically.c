#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
Given a string s. Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.
*/


#define TEXT "TO BE OR NOT TO BE"   // answer is ["TBONTB","OEROOE","   T"]

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **printVertically(char *s, int *returnSize) {
    // stack buf
    char b[200][1000];
    memset(b, 0, sizeof(b)*sizeof(char));

    int ch_len = strlen(s);

    // Split the space, find the maximum string
    int cnt = 0, split_cnt = 1;
    int max_len = 0;
    int i;
    for(i=0;i<ch_len;i++) {
        if(s[i] != ' ') {
            cnt++;
        }
        else {
            split_cnt++;
            if(max_len < cnt) {
                max_len = cnt;
            }
            cnt = 0;
        }
    }
    int *hash_start_i = (int *)malloc(split_cnt*sizeof(int));
    int *hash_ch_sz = (int *)malloc(split_cnt*sizeof(int));
    memset(hash_ch_sz, 0, split_cnt*sizeof(int));
    
    int k = 0;
    cnt = 0;
    for(i=0;i<ch_len;i++) {
        if(s[i] != ' ') {
            cnt++;
        }
        else {
            hash_ch_sz[k] = cnt;
            hash_start_i[k++] = i-1;
            cnt = 0;
        }
    }
    // last one
    hash_ch_sz[k] = cnt;
    hash_start_i[k++] = i-1;

    int temp = max_len;
    for(i=max_len-1;i>=0;i--) {
        for(int j=split_cnt-1;j>=0;j--) {
            // printf("debug: %d, %d\n", hash_ch_sz[j], hash_start_i[j]);
            if(temp - hash_ch_sz[j] > 0) {
                b[i][j] = ' ';
            }
            else {
                b[i][j] = s[hash_start_i[j]];
                hash_start_i[j]--;
                hash_ch_sz[j]--;
            }
        }
        temp--;
    }
    
    *returnSize = split_cnt;
    char **result = (char **)malloc(max_len * sizeof(char *));
    
    for (i=0;i<max_len; i++){
        result[i] =(char *)malloc((split_cnt+1)*sizeof(char));
        strcpy(result[i], b[i]);
    }

    return result;
}


int main() {
    printf("start\n");

    int return_size;
    char **ans_str = printVertically(TEXT, &return_size);

    for(int i=0;i<sizeof(ans_str)-1;i++) {    
        for(int j=0;j<return_size;j++) {
            printf("%c, ", ans_str[i][j]);
        }
        printf("\n");
    }

}
