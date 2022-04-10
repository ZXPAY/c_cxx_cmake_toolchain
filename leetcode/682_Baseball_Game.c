#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char *test_ops[] = {"5","2","C","D","+"};              // ans: 30
char *test_ops[] = {"5","-2","4","C","D","9","+","+"}; // ans: 27
#define OPS_SIZE  (sizeof(test_ops) / sizeof(test_ops[0]))

/*
You are keeping score for a baseball game with strange rules. The game consists of several rounds, where the scores of past rounds may affect future rounds' scores.

At the beginning of the game, you start with an empty record. You are given a list of strings ops, where ops[i] is the ith operation you must apply to the record and is one of the following:

An integer x - Record a new score of x.
"+" - Record a new score that is the sum of the previous two scores. It is guaranteed there will always be two previous scores.
"D" - Record a new score that is double the previous score. It is guaranteed there will always be a previous score.
"C" - Invalidate the previous score, removing it from the record. It is guaranteed there will always be a previous score.
Return the sum of all the scores on the record.
*/


typedef enum _state_em {
    STATE_ADD = 0,
    STATE_D = 1,
    STATE_C = 2,
    STATE_NUM = 3
} state_em;

int transfer_string_to_int(char *num) {
    int length = strlen(num);
    int i = 0;
    int val = 0;
    int neg_flag = 0;
    if(num[0] == '-') {
        // Negative
        i = 1;
        neg_flag = 1;
    }

    int deg = 1;
    for(int j=length-1;j>=i;j--) {
        assert(num[j]<='9' && num[j]>='0');
        val += ((int)num[j]-'0')*deg;
        deg *= 10;
    }

    if(neg_flag) {
        return -val;
    }
    return val;
}

int calPoints(char **ops, int opsSize) {
    int count = 0;
    int *list = malloc(opsSize*sizeof(int));
    state_em state;

    for(int i=0;i<opsSize;i++) {
        int length = strlen(ops[i]);
        if(length == 1) {
            if(*(ops[i]) == '+') {
                state = STATE_ADD;
                assert((count-2)>=0);
                list[count] = list[count-2] + list[count-1];
                count++;
            }
            else if(*(ops[i]) == 'D') {
                state = STATE_D;
                list[count] = list[count-1]*2;
                count++;
            }
            else if(*(ops[i]) == 'C') {
                state = STATE_C;
                count--;
            }
            else {
                state = STATE_NUM;
                list[count++] = transfer_string_to_int(ops[i]);
            }
        }
        else {
            state = STATE_NUM;
            list[count++] = transfer_string_to_int(ops[i]);
        }
        printf("state: %d\n", state);
        for(int k=0;k<count;k++) {
            printf("%d, ", list[k]);
        }
        printf("\n");
    }

    int result = 0;

    for(int i=0;i<count;i++) {
        result += list[i];
    }
    free(list);

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", calPoints(test_ops, OPS_SIZE));


}

