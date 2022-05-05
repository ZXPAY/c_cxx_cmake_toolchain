#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char c1[] = "123";
char c2[] = "456";

/* a mutiple b, get digit and carry */
int get_digit(char a, char b, int *carry) {
    int a_int = a - '0';
    int b_int = b - '0';
    int m = (a_int * b_int + (*carry));
    *carry = m / 10;
    return m % 10;
}

/* add digit to string */
void string_add(char *s, int i_s, char add_val) {
    int n = s[i_s] - '0' + add_val - '0';
    s[i_s] = n % 10 + '0';
    if(n >= 10) {
        string_add(s, i_s-1, (n/10)+'0');
    }
}

char *multiply(char *num1, char *num2){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char *result = malloc((len1+len2+1)*sizeof(char));
    for(int i=0;i<len1+len2;i++) {
        result[i] = '0';
    }
    result[len1+len2] = '\0';
    
    int carry = 0;
    int i_res = len1+len2-1;
    for(int i=len1-1;i>=0;i--) {
        /* Start at units digit index */
        i_res = (len1+len2-1) - (len1-1-i);
        for(int j=len2-1;j>=0;j--) {
            /* Get digit and carry */
            int n = get_digit(num1[i], num2[j], &carry);

            /* Add digit to result string, recursive method */
            string_add(result, i_res--, n+'0');            

            /* Last digit */
            if(j == 0 && carry > 0) {
                string_add(result, i_res--, carry+'0');            
                carry = 0;
            }
        }
    }
    
    // Remove '0'
    for(i_res=0;i_res<len1+len2-1;i_res++) {
        if(result[i_res] != '0') break;
    }

    return &result[i_res];
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    char *result = multiply(c1, c2);
    printf("(ans: 56088) %s x %s = %s", c1, c2, result);
}

