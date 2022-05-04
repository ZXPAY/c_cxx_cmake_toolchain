#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {1, 2, 3, 4};    // K=5, ans=2
// #define K 5

int test_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};    // K=2, ans=6
#define K 2

// int test_array[] = {3, 1, 3, 4, 3}; // K=6, ans=1
// #define K 6

#define ARRAY_SIZE (sizeof(test_array) / sizeof(int))

/* Linear hash */
#define HASH_SIZE (1000000000 / 32)
/* Using hash mapping */
int maxOperations_linear_hash(int *nums, int numsSize, int k) {
    uint32_t *linear_hash = malloc(HASH_SIZE*sizeof(uint32_t));
    memset(linear_hash, 0, HASH_SIZE*sizeof(uint32_t));

    int count = 0;
    /* X + Y = K => X = K-Y, search X or K-Y -> Get the same value */
    bool fg = 0;
    int cc = 0;
    for(int i=0;i<numsSize||fg;i++) {
        if(i == numsSize) i = 0;
        assert(nums[i] <= 1000000000UL);
        int k_y = k - nums[i];
        if(cc >= numsSize) break;
        cc++;
        if(k_y <= 0 || k_y >= k || nums[i] >= k || nums[i] == 0) continue;
        cc--;
        int i_hash_n = (k_y - 1) / 32;
        int i_hash_k = (k_y - 1) % 32;

        if(linear_hash[i_hash_n] & (1UL<<i_hash_k)) {
            count++;
            /* Clear k_y in hash */
            linear_hash[i_hash_n] &= ~(1UL<<i_hash_k);
            nums[i] = 0;
            cc = 0;
        }
        else {
            cc++;
            /* Insert x(nums[i]) into hash */
            i_hash_n = (nums[i] - 1) / 32;
            i_hash_k = (nums[i] - 1) % 32;
            if(linear_hash[i_hash_n] & (1UL<<i_hash_k)) {
                fg = 1;
                continue;
            }
            else {
                linear_hash[i_hash_n] |= (1UL<<i_hash_k);
                nums[i] = 0;
            }
        }
    }
    
    
    // for(int i=0;i<numsSize;i++) {
    //     printf("%d,", nums[i]);
    // }
    // printf("\n");

    return count;
}



/* Handle collision */
typedef struct _linklist_t {
    struct _linklist_t *next;
    int val;
} linklist_t;

linklist_t *generate_node(void) {
    linklist_t *node = (linklist_t *)malloc(sizeof(linklist_t));
    memset(node, 0, sizeof(linklist_t));

    return node;
}

void insert_chaining_hash(linklist_t **map, int index, int val, int numsSize) {
    // printf("insert hash[%d], val: %d\n", index, val);
    int hash_index = index % numsSize;
    linklist_t *temp = map[hash_index];
    if(temp == NULL) {
        // first time
        temp = generate_node();
        temp->val = val;
        map[hash_index] = temp;
        return;
    }
    // printf("alrealy %d\n", index);
    linklist_t *last = temp;
    for(;temp!=NULL;temp=temp->next) {
        last = temp;
    }

    temp = generate_node();
    temp->val = val;
    last->next = temp;
}

bool search_and_remove(linklist_t **map, int index, int val, int numsSize) {
    int hash_index = index%numsSize;
    for(linklist_t *a=map[index%numsSize];a!=NULL;a=a->next) {
        if(a->val == val) {
            map[hash_index] = map[hash_index]->next;
            // printf("Remove %d, %d\n", index, val);
            return true;
        }
    }

    return false;
}


/* Using hash mapping */
int maxOperations(int *nums, int numsSize, int k) {
    linklist_t **map = malloc(numsSize*sizeof(linklist_t *));
    memset(map, 0, numsSize*sizeof(linklist_t *));

    int count = 0;
    /* X + Y = K => X = K-Y, search X or K-Y -> Get the same value */
    for(int i=0;i<numsSize;i++) {
        int k_y = k - nums[i];
        if(k_y <= 0 || k_y >= k || nums[i] >= k) continue;
        if(search_and_remove(map, k_y, nums[i], numsSize)) {
            count++;
        }
        else {
            insert_chaining_hash(map, nums[i], k_y, numsSize);
        }
    }

    return count;
}

int cmp(int *a, int *b) {
    return *a - *b;
}

int maxOperations_sort(int *nums, int numsSize, int k) {
    /* nums => ascending */
    qsort(nums, numsSize, sizeof(int), cmp);
    
    int count = 0;
    int i_l = 0;
    int i_r = numsSize - 1;

    while(i_r > i_l) {
        if(nums[i_l] + nums[i_r] < k) {
            i_l++;
        }
        else if(nums[i_l] + nums[i_r] > k) {
            i_r--;
        }
        else if(nums[i_l] + nums[i_r] == k) {
            // equal to k
            count++;
            i_r--;
            i_l++;
        }
        else {
            assert(0);
        }
    }

    return count;
}

int maxOperations_n_square_solution(int *nums, int numsSize, int k) {
    int pick_num = 0;
    int count = 0;
    for(int i=0;i<numsSize;i++) {
        // pick nums[i]
        pick_num = nums[i];
        for(int j=0;j<numsSize;j++) {
            if(i == j) continue;
            if(nums[i] == -1 || nums[j] == -1) continue;
            if(pick_num + nums[j] == k) {
                // find and mark the nums array
                nums[i] = -1;
                nums[j] = -1;
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", maxOperations(test_array, ARRAY_SIZE, K));


}

