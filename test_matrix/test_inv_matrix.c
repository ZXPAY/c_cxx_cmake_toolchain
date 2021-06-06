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

    printf("=============================\n");
    printf("test 2x2 matrix inverse\n");
    float **mat22 = create_matrixf(2, 2);
    mat22[0][0] = 0.55;
    mat22[0][1] = 1.5;
    mat22[1][0] = 1.5;
    mat22[1][1] = 5;
    float **mat_inv22 = mat_inverse(mat22, 2);
    print_matrixf(mat_inv22, 2, 2);
    printf("answer is: \n");
    printf("10.0000, -3.0000,\n"); 
    printf("-3.0000, 1.1000,\n");

    printf("=============================\n");
    printf("test 4x4 matrix inverse\n");
    float **mat44 = create_matrixf(4, 4);
    mat44[0][0] = 0.55;
    mat44[0][1] = 1.5;
    mat44[0][2] = 1.5;
    mat44[0][3] = 5;
    mat44[1][0] = -1;
    mat44[1][1] = 0.5;
    mat44[1][2] = -0.5;
    mat44[1][3] = 1;
    mat44[2][0] = 1;
    mat44[2][1] = 1;
    mat44[2][2] = 0.8;
    mat44[2][3] = -0.1;
    mat44[3][0] = 0.1;
    mat44[3][1] = 0.2;
    mat44[3][2] = 0.3;
    mat44[3][3] = -5;

    float **mat_inv44 = mat_inverse(mat44, 4);
    print_matrixf(mat_inv44, 4, 4);
    printf("answer is: \n");
    printf("-0.5462622 , -0.27911666,  1.0837035 , -0.62375957, \n"); 
    printf("-0.21359041,  0.806666  ,  0.93122894, -0.07088178, \n");
    printf(" 0.95454115, -0.66105914, -1.2708313 ,  0.84774595 \n");
    printf(" 0.03780361, -0.01297924, -0.01732666, -0.1644457 ,\n");

}
