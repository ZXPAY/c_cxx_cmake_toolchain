#include "traverse_postorder_int.h"

void traverse_postorder_help_int(int *nums, int length, int index) {
    if(index >= length) return;

    int i_left = (index + 1) * 2 - 1;
    int i_right = (index + 1) * 2;


    traverse_postorder_help_int(nums, length, i_left);
    traverse_postorder_help_int(nums, length, i_right);
    tranvserse_postorder_handler_int(nums[index]);
    
}


void traverse_postorder_int(int *nums, int length) {
    traverse_postorder_help_int(nums, length, 0);
}


__attribute__((weak)) void tranvserse_postorder_handler_int(int value) {
    __asm("nop");
}
