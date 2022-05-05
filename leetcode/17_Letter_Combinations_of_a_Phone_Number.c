#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_digits[] = "29";

char *phone_letter_map[] = {
    NULL,
    NULL,
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};
int phone_letter_sz[] = {
    0,
    0,
    3,
    3,
    3,
    3,
    3,
    4,
    3,
    4,
};

bool incre_i_digits(int *ch_count, int i_digit, int digits_len, int *digit_map) {
    if(i_digit >=  digits_len) return false;
    int i_ch = ch_count[i_digit];
    ch_count[i_digit]++;
    if(i_ch+1 >= phone_letter_sz[digit_map[i_digit]]) {
        ch_count[i_digit] = 0;
        return incre_i_digits(ch_count, i_digit+1, digits_len, digit_map);
    }
    return true;
}

char **letterCombinations(char *digits, int *returnSize) {
    if(digits == NULL) return NULL;
    int len_digits = strlen(digits);
    if(len_digits == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int *index_phone = malloc(len_digits*sizeof(int));

    int *i_digits = malloc(len_digits*sizeof(int));
    memset(i_digits, 0, len_digits*sizeof(int));

    /* Prepare the result memory */
    int max_len = 1;
    for(int i=0;i<len_digits;i++) max_len *= 16;
    char **result = malloc(max_len*sizeof(char *));
    for(int i=0;i<max_len;i++) {
        result[i] = malloc((len_digits+1)*sizeof(char));
        memset(result[i], 0, (len_digits+1)*sizeof(char));
    }

    for(int i=0;i<len_digits;i++) {
        index_phone[i] = digits[i] - '0';
    }
    
    int i_res = 0;
    bool fg = 1;
    while(fg) {
        for(int j=0;j<len_digits;j++) {
            result[i_res][j] = phone_letter_map[index_phone[j]][i_digits[j]];
        }
        i_res++;
        fg = incre_i_digits(i_digits, 0, len_digits, index_phone);
    }

    *returnSize = i_res;

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_sz = 0;
    char **result = letterCombinations(test_digits, &return_sz);

    printf("{");
    for(int i=0;i<return_sz;i++) {
        printf("%s,", result[i]);
    }
    printf("}\n");
}

