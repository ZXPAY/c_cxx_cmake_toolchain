#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_array[] = {1,8,6,2,5,4,8,3,7};
#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

int maxArea(int *height, int heightSize) {
    int i_left = 0;
    int i_right = heightSize - 1;
    int max_val = 0;
    while(i_left < i_right) {
        int h = height[i_left] < height[i_right] ? height[i_left] : height[i_right];
        int temp_area = h*(i_right - i_left);
        if(temp_area > max_val) max_val = temp_area;

        if(height[i_left] < height[i_right]) {
            i_left++;
        }
        else {
            i_right--;
        }

    }
    return max_val;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", maxArea(test_array, ARRAY_SIZE));

}

