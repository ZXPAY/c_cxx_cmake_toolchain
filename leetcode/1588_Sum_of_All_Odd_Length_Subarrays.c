#include <stdio.h>
#include <stdlib.h>

int test_array[] = {1, 4, 2, 5, 3};
// int test_array[] = {1, 2};
// int test_array[] = {10, 11, 12};


int sumOddLengthSubarrays(int *arr, int arrSize) {
    int sum_v = 0;
    int temp_odd_length = 1;
    // index: 
    // 0             1       2      3      4 
    // 0,1,2         1,2,3  2,3,4
    // 0,1,2,3,4,5
    int st, end;
    for(;temp_odd_length<=arrSize;temp_odd_length+=2) {
        st = 0;
        end = st + temp_odd_length - 1;
        for(int i=0;i<arrSize;i=st) {
            printf("%d: %d,%d\n", i, st, end);
            for(int j=st;j<=end;j++) {
                sum_v += *(arr+j);
            }
            st++;
            end++;
            if(end >= arrSize) {
                break;
            }
        }
    }
    return sum_v;
}


int main () {
    printf("start \n");
    printf("sumOddLengthSubarrays: %d\n", sumOddLengthSubarrays(test_array, sizeof(test_array)/sizeof(int)));

}

