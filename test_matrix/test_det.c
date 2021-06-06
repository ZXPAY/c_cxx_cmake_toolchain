#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dmatrix2d.h"

int main() {
    printf("start \n");
    
    float **test_matrix = (float **)malloc(sizeof(float *)*3);
    for(int i=0;i<3;i++) {
        test_matrix[i] = (float *)malloc(sizeof(float)*3);
    }

    test_matrix[0][0] = 1;
    test_matrix[0][1] = 5;
    test_matrix[0][2] = 3;
    test_matrix[1][0] = 2;
    test_matrix[1][1] = 5;
    test_matrix[1][2] = 6;
    test_matrix[2][0] = 3;
    test_matrix[2][1] = 8;
    test_matrix[2][2] = -5;

    printf("matrix: \n");
    print_matrixf(test_matrix, 3, 3);
    printf("determinent of matrix: %.2f\n", detf(test_matrix, 3, 0));
    printf("answer should be 70.\n");

    float **test_matrix2 = (float **)malloc(sizeof(float *)*4);
    for(int i=0;i<4;i++) {
        test_matrix2[i] = (float *)malloc(sizeof(float)*4);
    }


    test_matrix2[0][0] = 1;
    test_matrix2[0][1] = 1;
    test_matrix2[0][2] = 0;
    test_matrix2[0][3] = 1;
    test_matrix2[1][0] = 1;
    test_matrix2[1][1] = 1;
    test_matrix2[1][2] = 1;
    test_matrix2[1][3] = 0;
    test_matrix2[2][0] = 0;
    test_matrix2[2][1] = 1;
    test_matrix2[2][2] = 1;
    test_matrix2[2][3] = 1;
    test_matrix2[3][0] = 1;
    test_matrix2[3][1] = 0;
    test_matrix2[3][2] = 1;
    test_matrix2[3][3] = 1;

    printf("matrix2: \n");
    print_matrixf(test_matrix2, 4, 4);
    printf("determinent of matrix2: %.2f\n", detf(test_matrix2, 4, false));
    printf("answer should be -3.\n");
}
