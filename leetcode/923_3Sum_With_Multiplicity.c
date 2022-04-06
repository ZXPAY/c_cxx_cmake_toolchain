#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// int test_array[] = {1,1,2,2,3,3,4,4,5,5};
int test_array[] = {2,2,3,2};
#define TARGET 7
#define ARRAY_SIZE   (sizeof(test_array) / sizeof(int))

/*
Given an integer array arr, and an integer target, return the number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.

As the answer can be very large, return it modulo 109 + 7.
*/

#define MOD  1000000007L

int cmp(int *a, int *b) {
    return *a - *b;
}
int threeSumMulti(int *arr, int arrSize, int target) {
    qsort(arr, arrSize, sizeof(int), cmp);
    long ans = 0;
    for (int i = 0; i < arrSize; ++i) {
        // We'll try to find the number of i < j < k
        // with arr[j] + arr[k] == T, where T = target - A[i].

        // The below is a "two sum with multiplicity".
        int T = target - arr[i];
        int j = i+1, k = arrSize - 1;

        while (j < k) {
            // These steps proceed as in a typical two-sum.
            if (arr[j] + arr[k] < T)
                j++;
            else if (arr[j] + arr[k] > T)
                k--;
            else if (arr[j] != arr[k]) {  // We have arr[j] + arr[k] == T.
                // Let's count "left": the number of arr[j] == A[j+1] == A[j+2] == ...
                // And similarly for "right".
                int left = 1, right = 1;
                while (j+1 < k && arr[j] == arr[j+1]) {
                    left++;
                    j++;
                }
                while (k-1 > j && arr[k] == arr[k-1]) {
                    right++;
                    k--;
                }

                ans += left * right;
                ans %= MOD;
                j++;
                k--;
            } else {
                // M = k - j + 1
                // We contributed M * (M-1) / 2 pairs.
                ans += (k-j+1) * (k-j) / 2;
                ans %= MOD;
                break;
            }
        }
    }

    return ans;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }



    printf("result: %d\n", threeSumMulti(test_array, ARRAY_SIZE, TARGET));

}

