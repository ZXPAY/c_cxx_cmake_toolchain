#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "traverse_preorder_int.h"
#include "traverse_inorder_int.h"
#include "traverse_postorder_int.h"


/*
* left node:    (i+1)*2
* right node:   (i+1)*2 + 1
* parrent node: i/2
*/

/*
                5
        2               6
    1       4       X       7
   X X     3 X     X X     X  X

pre-order:  5, 2, 1, 4, 3, 6, 7
in-order:   1, 2, 3, 4, 5, 6, 7
post-order: 1, 3 ,4, 2, 7, 6, 5
*/


int test_array[] = {
    5, 2, 6, 1, 4, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0 
};
#define ARRAY_SIZE  (sizeof(test_array) / sizeof(int))


void traverse_preorder(int index) {
    if(index >= ARRAY_SIZE) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;

    if(test_array[index] != 0){
        printf("%d, ", test_array[index]);
    }

    traverse_preorder(i_left);
    traverse_preorder(i_right);
    
}

void traverse_inorder(int index) {
    if(index >= ARRAY_SIZE) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    traverse_inorder(i_left);

    if(test_array[index] != 0){
        printf("%d, ", test_array[index]);
    }

    traverse_inorder(i_right);
    
}

void traverse_postorder(int index) {
    if(index >= ARRAY_SIZE) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    traverse_postorder(i_left);
    traverse_postorder(i_right);
    
    if(test_array[index] != 0){
        printf("%d, ", test_array[index]);
    }
}

int main() {
    printf("start\n");
    
    for(int i=0;i<sizeof(test_array)/sizeof(int);i++) {
        printf("%d, ", test_array[i]);
    }
    printf("\n");

    printf("start traverse\n");
    
    traverse_preorder(0);
    printf("\n");

    traverse_inorder(0);
    printf("\n");
    
    traverse_postorder(0);
    printf("\n");
    
    printf("start traverse in source files\n");

    // print in hanlder function
    traverse_preorder_int(test_array, ARRAY_SIZE);
    printf("\n");

    // print in hanlder function
    traverse_inorder_int(test_array, ARRAY_SIZE);
    printf("\n");

    // print in hanlder function
    traverse_postorder_int(test_array, ARRAY_SIZE);
    printf("\n");

}

void tranvserse_preorder_handler_int(int value) {
    if(value != 0) printf("%d, ", value);
}
void tranvserse_inorder_handler_int(int value) {
    if(value != 0) printf("%d, ", value);
}
void tranvserse_postorder_handler_int(int value) {
    if(value != 0) printf("%d, ", value);
}
