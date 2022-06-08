#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int nums1[] = {1,2,3,0,0,0};
int M = 3;
int nums2[] = {2,5,6};
int N = 3;

#define NUMS_SIZEOF(x) (sizeof(x) / sizeof(int))

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n) {
    if(nums1Size == 0) return nums2;
    else if(n == 0) return nums1;

    int *temp = malloc(nums1Size*sizeof(int));

    int i = 0;
    int i1 = 0;
    int i2 = 0;
    while(i<nums1Size) {
        printf("%d,%d\n", i1, i2);
        if(i1 >= m) {
            temp[i++] = nums2[i2++];
        }
        else if(i2 >= n) {
            temp[i++] = nums1[i1++];
        }
        else if(nums1[i1] < nums2[i2]) {
            temp[i++] = nums1[i1++];
        }
        else {
            temp[i++] = nums2[i2++];
        }
    }
    memcpy(nums1, temp, nums1Size*sizeof(int));

    free(temp);
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    merge(nums1, NUMS_SIZEOF(nums1), M, nums2, NUMS_SIZEOF(nums2), N);

    printf("{");
    for(int i=0;i<NUMS_SIZEOF(nums1);i++) {
        printf("%d,", nums1[i]);
    }
    printf("}\n");


}

