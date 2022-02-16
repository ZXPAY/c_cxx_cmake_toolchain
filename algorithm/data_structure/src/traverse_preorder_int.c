#include "traverse_preorder_int.h"

void traverse_preorder_help_int(int *nums, int length, int index) {
    if(index >= length) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    tranvserse_preorder_handler_int(nums[index]);
    traverse_preorder_help_int(nums, length, i_left);
    traverse_preorder_help_int(nums, length, i_right);
    
}


void traverse_preorder_int(int *nums, int length) {
    traverse_preorder_help_int(nums, length, 0);
}


__attribute__((weak)) void tranvserse_preorder_handler_int(int value) {
    __asm("nop");
}
