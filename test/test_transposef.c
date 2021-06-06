#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "dmatrix2d.h"

int main() {
    printf("start \n");
    
    float **test_matrix = (float **)malloc(sizeof(float *)*3);
    for(int i=0;i<3;i++) {
        test_matrix[i] = (float *)malloc(sizeof(float)*2);
    }

    test_matrix[0][0] = 1;
    test_matrix[0][1] = 2;
    test_matrix[1][0] = 3;
    test_matrix[1][1] = 4;
    test_matrix[2][0] = 5;
    test_matrix[2][1] = 6;

    printf("Origin matrix: \n");
    print_matrixf(test_matrix, 3, 2);
    printf("Do transpose: \n");
    test_matrix = transposef(test_matrix, 3, 2);
    print_matrixf(test_matrix, 2, 3);

}
