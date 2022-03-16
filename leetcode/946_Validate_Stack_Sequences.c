#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* false */
int test_pushed[] = {4,0,1,2,3};
int test_popped[] = {4,2,3,0,1};

/* true */
// int test_pushed[] = {4,0,1,2,3};
// int test_popped[] = {4,2,3,1,0};

#define PUSHED_SIZE (sizeof(test_pushed) / sizeof(int))
#define POPPED_SIZE (sizeof(test_popped) / sizeof(int))

/*
Given two integer arrays pushed and popped each with distinct values, return true if this could have been the result of a sequence of push and pop operations on an initially empty stack, or false otherwise.
*/

bool validateStackSequences(int *pushed, int pushedSize, int *popped, int poppedSize) {
    // help(pushed, 0, popped, 0, poppedSize);
    assert(pushedSize==poppedSize);
    int *buf = malloc(pushedSize*sizeof(int));
    memset(buf, 0, pushedSize*sizeof(int));

    int i_pop = 0;
    int i_buf = 0;
    int i_push = 0;
    
    for(int i=0;i<pushedSize*2;i++) {
        if(i_buf == 0) {
            // buf is empty, push to buf
            printf("push: %d\n", pushed[i_push]);
            buf[i_buf++] = pushed[i_push++];
        }
        else {
            if(buf[i_buf-1] != popped[i_pop] && i_push < pushedSize) {
                // push
                printf("push: %d\n", pushed[i_push]);
                buf[i_buf++] = pushed[i_push++];
            }
            else {
                // pop
                printf("pop: %d, buf is: %d\n", popped[i_pop], buf[i_buf-1]);
                if(buf[i_buf-1] != popped[i_pop]) return false;
                i_buf--;
                i_pop++;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("%d\n", validateStackSequences(test_pushed, PUSHED_SIZE, test_popped, POPPED_SIZE));

}

