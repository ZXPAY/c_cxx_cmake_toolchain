#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {-1,0,1,2,-1,-4};
int test_array[] = {-1,5,-1,3,0,9,10,-2,-5,-20,15};
// int test_array[] = {0, 0, 0};
#define ARRAY_SIZE   (sizeof(test_array) / sizeof(int))

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


int cmp(int *a, int *b) {
    return *a - *b;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmp);

    // for(int i=0;i<numsSize;i++) {
    //     printf("%d, ", nums[i]);
    // }
    // printf("\n");

    int **result = NULL;
    int left = 0;

    *returnSize = 0;
    int count = 0;
    result = (int **)realloc(result, sizeof(int *) * 20000);
    memset(result, 0, sizeof(int *)*20000);
    
    while(left < numsSize-1) {
        int target = nums[left];
        if(target > 0) break;
        int i = left + 1;
        int j = numsSize - 1;

        // Handle duplicated
        if(left > 0 && nums[left] == nums[left-1]) {
            left++;
            continue;
        }

        while(i < j) {
            int sum = target + nums[i] + nums[j];
            // printf("%d, %d -> %d, %d, %d\n", i, j, target, nums[i], nums[j]);
            if(sum == 0) {
                count++;
                result[count-1] = malloc(3*sizeof(int));
                result[count-1][0] = target;
                result[count-1][1] = nums[i];
                result[count-1][2] = nums[j];
                printf("%d, %d, %d\n", target, nums[i], nums[j]);

                // Handle duplicated
                while(i < j && nums[i] == nums[i+1]) i++;
                while(i < j && nums[j] == nums[j-1]) j--;
            }
            if(sum > 0)
                j--;
            else
                i++;
        }
        left++;
    }
    *returnSize = count;
    
    *returnColumnSizes = malloc(sizeof(int)*count);
    for(int i=0;i<count;i++) {
        *((*returnColumnSizes)+i) = 3;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    int return_size;
    int *return_col;
    int **result = threeSum(test_array, ARRAY_SIZE, &return_size, &return_col);

    printf("result\n");
    for(int i=0;i<return_size;i++) {
        for(int j=0;j<return_col[i];j++) {
            printf("%d, ", result[i][j]);
        }
        printf("\n");
    }


}

