#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// ans: {1, 2}
int test_array[] = {
    1,1,1,2,2,3
};
#define K 2

#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

// Quick sort in math library
extern void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

typedef struct _freq_info_t {
    int value;
    int count;
} freq_info_t;

/* low -> hight */
static int cmp(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/* high count -> low count */
static int cmp_count(const void * a, const void * b) {
   return ((freq_info_t *)b)->count - ((freq_info_t *)a)->count;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *topKFrequent(int *nums, int numsSize, int k, int *returnSize){
    freq_info_t *info = malloc(sizeof(freq_info_t)*numsSize);
    memset(info, 0, sizeof(freq_info_t)*numsSize);
    int *result = malloc(sizeof(int)*k);

    qsort(nums, numsSize, sizeof(int), cmp);

    int i_info = 0;
    info[0].value = nums[0];
    info[0].count = 1;
    for(int i=1;i<numsSize;i++) {
        if(info[i_info].value != nums[i]) {
            // new value
            i_info++;
            info[i_info].value = nums[i];
            info[i_info].count = 1;
        }
        else {
            // increment the count
            info[i_info].count++;
        }
    }

    assert((i_info+1)>=k);

    // Sorting the info
    qsort(info, i_info+1, sizeof(freq_info_t), cmp_count);

    for(int i=0;i<i_info+1;i++) {
        printf("[%d]: %d\n", info[i].value, info[i].count);
    }

    for(int i=0;i<k;i++) {
        result[i] = info[i].value;
    }
    *returnSize = k;

    free(info);

    return result;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int return_size = 0;
    int *result = topKFrequent(test_array, ARRAY_SIZE, K, &return_size);

    printf("result: {");
    for(int i=0;i<return_size;i++) {
        printf("%d, ", result[i]);
    }
    printf("}\n");


}

