#include <stdio.h>
#include <stdbool.h>
#include "dmatrix2d.h"

int main() {
    float **mat = create_matrixf(3, 3);
    mat[0][0] = 1;
    mat[0][1] = 5;
    mat[0][2] = 3;
    mat[1][0] = 2;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 3;
    mat[2][1] = 8;
    mat[2][2] = -5;

    printf("test matrix: \n");
    print_matrixf(mat, 3, 3);

    printf("inverse matrix: \n");
    float **mat_inv = mat_inverse(mat, 3);
    print_matrixf(mat_inv, 3, 3);

    printf("\nmat multify mat_inv, should be identity matrix\n");
    float **mat_mul_inv_mat = mat_mul(mat, mat_inv, 3, 3, 3);
    print_matrixf(mat_mul_inv_mat, 3, 3);


    printf("test 2x2 matrix inverse\n");
    float **mat22 = create_matrixf(2, 2);
    mat22[0][0] = 0.55;
    mat22[0][1] = 1.5;
    mat22[1][0] = 1.5;
    mat22[1][1] = 5;
    float **mat_inv22 = mat_inverse(mat22, 2);
    print_matrixf(mat_inv22, 2, 2);


}
