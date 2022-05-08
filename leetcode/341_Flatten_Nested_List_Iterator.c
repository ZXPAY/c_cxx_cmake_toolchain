#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


/* Define the NestedList */

struct NestedInteger {
    int value;
    int nested_count;
    struct NestedInteger **nested_list;
};

struct NestedInteger *generate_nested_node(int value, int nested_sz) {
    struct NestedInteger *nested_int = (struct NestedInteger *) malloc(sizeof(struct NestedInteger));
    memset(nested_int, 0, sizeof(struct NestedInteger));

    if(nested_sz > 0) {
        nested_int->nested_list = (struct NestedInteger **)malloc(nested_sz*sizeof(struct NestedInteger *));
        memset(nested_int->nested_list, 0, nested_sz*sizeof(struct NestedInteger *));
    }

    nested_int->nested_count = nested_sz;
    nested_int->value = value;

    return nested_int;
}

void link_nested(struct NestedInteger *nested_int, struct NestedInteger *nested_next) {
    nested_int->nested_list[nested_int->nested_count++] = nested_next;
}

// Return true if this NestedInteger holds a single integer, rather than a nested list.
bool NestedIntegerIsInteger(struct NestedInteger *nested_int) {
    if(nested_int->nested_list == NULL) return true;
    return false;
}

// Return the single integer that this NestedInteger holds, if it holds a single integer
// The result is undefined if this NestedInteger holds a nested list
int NestedIntegerGetInteger(struct NestedInteger *nested_int) {
    if(nested_int->nested_list == NULL) return nested_int->value;
    return -1;
}

// Return the nested list that this NestedInteger holds, if it holds a nested list
// The result is undefined if this NestedInteger holds a single integer
struct NestedInteger **NestedIntegerGetList(struct NestedInteger *nested_int) {
    return nested_int->nested_list;
}

// Return the nested list's size that this NestedInteger holds, if it holds a nested list
// The result is undefined if this NestedInteger holds a single integer
int NestedIntegerGetListSize(struct NestedInteger *nested_int) {
    return nested_int->nested_count;
}

/* Solution 1 start */

// struct NestedIterator {
//     int index;
//     int count;
//     int array[50000];
// };

// void help(struct NestedInteger **nestedList, int i_nested, int nestedListSize, int *arr, int *i_arr) {
//     if(i_nested >= nestedListSize) return;
//     // printf("%p, %d, %d\n", nestedList, i_nested, nestedListSize);

//     if(NestedIntegerIsInteger(nestedList[i_nested])) {
//         // printf("%d\n", NestedIntegerGetInteger(nestedList[i_nested]));
//         arr[(*i_arr)++] = NestedIntegerGetInteger(nestedList[i_nested]);
//     }


//     int next_nestedsize = NestedIntegerGetListSize(nestedList[i_nested]);
//     help(NestedIntegerGetList(nestedList[i_nested]), 0, next_nestedsize, arr, i_arr);
//     help(nestedList, i_nested+1, nestedListSize, arr, i_arr);
// }

// struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList, int nestedListSize) {
//     struct NestedIterator *iter = malloc(sizeof(struct NestedIterator));
//     memset(iter, 0, sizeof(struct NestedIterator));
//     help(nestedList, 0, nestedListSize, iter->array, &iter->count);
//     return iter;
// }

// bool nestedIterHasNext(struct NestedIterator *iter) {
//     if(iter->index<iter->count) return true;
//     return false;
// }

// int nestedIterNext(struct NestedIterator *iter) {
//     if(iter->index<iter->count) return iter->array[iter->index++];
//     return -1;
// }

// /** Deallocates memory previously allocated for the iterator */
// void nestedIterFree(struct NestedIterator *iter) {
//     free(iter);
// }

/* Solution 1 end */


/* Solution 2 start */

#define NESTED_ITERATOR_BUF 1000
struct NestedIterator {
    int index;
    struct NestedInteger **buf;
};

struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList, int nestedListSize) {
    struct NestedIterator *iter = (struct NestedIterator *) malloc(sizeof(struct NestedIterator));
    iter->buf = (struct NestedInteger **)malloc(sizeof(struct NestedInteger *)*NESTED_ITERATOR_BUF);
    iter->index = nestedListSize - 1;

    for(int i=0;i<nestedListSize;i++) {
        iter->buf[i] = nestedList[nestedListSize - i - 1];
    }

    return iter;
}

bool nestedIterHasNext(struct NestedIterator *iter) {
    assert(iter != NULL);
    if(iter->index >= 0) {
        /* Go and find the nested end integer */
        while(!NestedIntegerIsInteger(iter->buf[iter->index])) {
            struct NestedInteger **temp = NestedIntegerGetList(iter->buf[iter->index]);
            int list_sz = NestedIntegerGetListSize(iter->buf[iter->index]);
            if(iter->index == 0 && list_sz == 0) return 0;
            for(int i=0;i<list_sz;i++) {
                iter->buf[iter->index+i] = temp[list_sz - i - 1];
            }
            iter->index += list_sz - 1;
        }
        return 1;
    }

    return 0;
}

int nestedIterNext(struct NestedIterator *iter) {
    if(iter->index<0) return -1;
    return NestedIntegerGetInteger(iter->buf[iter->index--]);
}

/** Deallocates memory previously allocated for the iterator */
void nestedIterFree(struct NestedIterator *iter) {
    free(iter->buf);
    free(iter);
}

/* Solution 2 end */

/**
 * Your NestedIterator will be called like this:
 * struct NestedIterator *i = nestedIterCreate(nestedList, nestedListSize);
 * while (nestedIterHasNext(i)) printf("%d\n", nestedIterNext(i));
 * nestedIterFree(i);
 */

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    /* test nested integer array [[1,1],2,[3,4,[10,2]]] */
    struct NestedInteger *root = generate_nested_node(-1, 3);

    root->nested_list[0] = generate_nested_node(-1, 2);
    root->nested_list[1] = generate_nested_node(2, 0);
    root->nested_list[2] = generate_nested_node(-1, 3);

    root->nested_list[0]->nested_list[0] = generate_nested_node(1, 0);
    root->nested_list[0]->nested_list[1] = generate_nested_node(1, 0);

    root->nested_list[2]->nested_list[0] = generate_nested_node(3, 0);
    root->nested_list[2]->nested_list[1] = generate_nested_node(4, 0);
    root->nested_list[2]->nested_list[2] = generate_nested_node(-1, 2);

    root->nested_list[2]->nested_list[2]->nested_list[0] = generate_nested_node(10, 0);
    root->nested_list[2]->nested_list[2]->nested_list[1] = generate_nested_node(2, 0);

    struct NestedIterator *iter = nestedIterCreate(root->nested_list, NestedIntegerGetListSize(root));

    printf("{");
    while(nestedIterHasNext(iter)) {
        printf("%d,", nestedIterNext(iter));
    }
    printf("}\n");

    nestedIterFree(iter);

}

