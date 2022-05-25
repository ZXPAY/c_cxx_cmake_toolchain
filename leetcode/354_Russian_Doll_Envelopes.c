#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define ENV_SZ 4
int test_envelopes[4][2] = {
    {5, 4},
    {6, 4},
    {6, 7},
    {2, 3}
};

int cmp(const void *a, const void *b) {
    if((*(int **)a)[0] == (*(int **)b)[0])
        return (*(int **)b)[1] - (*(int **)a)[1];
    else return (*(int **)a)[0] - (*(int **)b)[0];
}


int search(int *dp, int i_left, int i_right, int target) {
    if(i_left >= i_right) return i_left;
    int i_mid = (i_left + i_right) / 2;

    if(dp[i_mid] == target) {
        return i_mid;
    }
    else if(dp[i_mid] > target) {
        return search(dp, i_left, i_mid, target);
    }
    else {
        return search(dp, i_mid+1, i_right, target);
    }

    return i_left;
}

int maxEnvelopes(int **envelopes, int envelopesSize, int *envelopesColSize) {
    qsort(envelopes, envelopesSize, sizeof(int **), cmp);

    int *dp = malloc(envelopesSize*sizeof(int));
    int index = 1;
    dp[0] = envelopes[0][1];

    for(int i = 1; i < envelopesSize; i++) {
        if(envelopes[i][1] > dp[index - 1]) {
            dp[index++] = envelopes[i][1];
        }
        else {
            int temp = search(dp, 0, index, envelopes[i][1]);
            dp[temp] = envelopes[i][1];
            if(temp == index)
                index++;
        }
    }
    return index;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    int **envolopes = malloc(ENV_SZ*sizeof(int *));
    int *col = malloc(ENV_SZ*sizeof(int));
    for(int i=0;i<ENV_SZ;i++) {
        envolopes[i] = malloc(2*sizeof(int));
        memcpy(envolopes[i], test_envelopes[i], 2*sizeof(int));
        col[i] = 2;
    }
    printf("result: %d\n", maxEnvelopes(envolopes, ENV_SZ, col));


}

