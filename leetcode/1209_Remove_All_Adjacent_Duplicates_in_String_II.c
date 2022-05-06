#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/* ans: aa */
char test_string2[] = "deeedbbcccbdaa";
char test_string[] = "deeedbbcccbdaa";
#define K 3

void sol1_time_limit(char *s, int length, int i_st, char prev, int *dup_index, int *count, int k) {
    if(i_st > length) return;

    // printf("[%d]  %c: %d\n", i_st, prev, *count);

    if(*count == k) {
        for(int i=0;i<k;i++) {
            // printf("== %d\n", dup_index[i]);
            s[dup_index[i]] = '0';
        }
        *count = 0;
        // printf("%s\n", s);
        sol1_time_limit(s, length, 0, s[0], dup_index, count, k);
    }
    else if(s[i_st] == '0') {
        /* Pass if prev is '0' */
        sol1_time_limit(s, length, i_st+1, prev, dup_index, count, k);
    }
    else if(s[i_st] == prev) {
        dup_index[(*count)++] = i_st;
        sol1_time_limit(s, length, i_st+1, prev, dup_index, count, k);
    }
    else {
        *count = 0;
        sol1_time_limit(s, length, i_st, s[i_st], dup_index, count, k);
    }
}
char *removeDuplicates_2(char *s, int k) {
    assert(k>1);
    int length = strlen(s);

    int *dup_index = malloc(k*sizeof(int));
    int count = 0;
    sol1_time_limit(s, length, 0, s[0], dup_index, &count, k);

    int i_s = 0;
    for(int i=0;i<length;i++) {
        if(s[i] != '0') {
            s[i_s++] = s[i];
        }
    }
    s[i_s] = '\0';

    return s;
}


char *removeDuplicates(char *s, int k) {
    assert(k>1);
    int length = strlen(s);

    char *stack_buf = malloc(length*sizeof(char));
    int i_stack = 0;

    int repeat_count = 0;
    for(int i=0;i<length;i++) {
        /* Push into stack buf, i_stack start from 1 */
        stack_buf[i_stack++] = s[i];

        /* Determine whether adjacent is the same */
        if(i_stack >= 2) {
            if(stack_buf[i_stack-2] == stack_buf[i_stack-1]) {
                repeat_count++;
            }
            else {
                repeat_count = 1;
            }
        }

        /* Determine the counter */
        if(repeat_count == k) {
            /* Pop the stack */
            i_stack -= k;

            /* Get the repeat counter in stack */
            repeat_count = 1;
            int temp = i_stack-1;
            while(temp-1 >= 0) {
                if(stack_buf[temp] == stack_buf[temp-1]) {
                    repeat_count++;
                }
                else {
                    break;
                }
                temp--;
            }
        }

        // for(int i=0;i<i_stack;i++) {
        //     printf("%c", stack_buf[i]);
        // }
        // printf("\n");
    }

    /* Put the stack to s buf */
    for(int i=0;i<i_stack;i++) {
        s[i] = stack_buf[i];
    }
    s[i_stack] = '\0';

    return s;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("result: %s\n", removeDuplicates_2(test_string2, K));
    printf("result: %s\n", removeDuplicates(test_string, K));


}

