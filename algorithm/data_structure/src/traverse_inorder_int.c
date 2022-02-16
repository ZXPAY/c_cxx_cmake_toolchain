#include "traverse_inorder_int.h"

void traverse_inorder_help_int(int *nums, int length, int index) {
    if(index >= length) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    traverse_inorder_help_int(nums, length, i_left);
    tranvserse_inorder_handler_int(nums[index]);
    traverse_inorder_help_int(nums, length, i_right);
    
}


void traverse_inorder_int(int *nums, int length) {
    traverse_inorder_help_int(nums, length, 0);
}


__attribute__((weak)) void tranvserse_inorder_handler_int(int value) {
    __asm("nop");
}
