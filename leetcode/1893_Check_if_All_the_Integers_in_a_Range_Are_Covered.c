#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
You are given a 2D integer array rangesand two integers left and right. Each ranges[i] = [starti, endi] represents an inclusive interval between starti and endi.

Return true if each integer in the inclusive range [left, right] is covered by at least one interval in ranges. Return false otherwise.

An integer x is covered by an interval ranges[i] = [starti, endi] if starti <= x <= endi.
*/
 
// const int test_ranges[3][2] = {   // answer true
//     {1,2},
//     {3,4},
//     {5,6}
// };
const int test_ranges[1][2] = {   // answer false
    {1, 1}
};

// const int test_ranges[2][2] = {   // answer false
//     {1,10},
//     {10,20},
// };

#define ROW  1
#define COL  2

bool isCovered(int **ranges, int rangesSize, int *rangesColSize, int left, int right) {
    int cnt = 0;
    int last;
    for(int r=0;r<rangesSize;r++) {
        cnt = 0;
        for(int c=0;c<*rangesColSize;c++) {
            if(ranges[r][c] >= left && ranges[r][c] <= right) {
                cnt++;
            }
            if(c == 0) {
                last = ranges[r][c];
            }
            else {
                if(last == ranges[r][c]) {
                    return false;
                }
            }
        }
        if(0 == cnt) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("start\n");

    int **ranges = (int **)malloc(ROW*sizeof(int));
    for(int i=0;i<ROW;i++) ranges[i] = (int *)malloc(COL*sizeof(int));

    for(int i=0;i<ROW;i++) {
        for(int j=0;j<COL;j++) {
            ranges[i][j] = test_ranges[i][j];
            printf("%d, ", ranges[i][j]);
        }
        printf("\n");
    }

    int rangeSize = ROW;
    int rangeCol = COL;
    printf("isCovered: %d\n", isCovered(ranges, rangeSize, &rangeCol, 1, 1));

}
