#include <stdio.h>
#include <stdbool.h>
#include "dmatrix2d.h"

int main() {
    float **mat = create_matrixf(3, 3);
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;

    printf("test matrix: \n");
    print_matrixf(mat, 3, 3);

    float **mat_cof = create_matrixf(2, 2);
    for(int c=0;c<3;c++) {
        printf("Get cofator select mat[0][%d]\n", c);
        mat_cofactor(mat, mat_cof, 0, c, 3);
        print_matrixf(mat_cof, 2, 2);
    }
    printf("->%p\n", mat);
    printf("%f\n", detf(mat, 3, false));

}