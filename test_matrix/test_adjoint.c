#include <stdio.h>
#include <stdbool.h>
#include "dmatrix2d.h"

int main() {
    float **mat = create_matrixf(3, 3);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = -1;
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = -2;
    mat[2][0] = 1;
    mat[2][1] = 0;
    mat[2][2] = 1;

    printf("test matrix: \n");
    print_matrixf(mat, 3, 3);

    printf("adjoint matrix: \n");
    float **mat_adj = mat_adjoint(mat, 3);
    print_matrixf(mat_adj, 3, 3);
}
