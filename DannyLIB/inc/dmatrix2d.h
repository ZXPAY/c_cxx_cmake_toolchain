#ifndef DMATRIX2D_H
#define DMATRIX2D_H

#define MAX_ITER_DET_MATRIX  30

float **create_matrixf(int row, int col);
void delete_matrixf(float **mat);
float **mat_mul(float **mat1, float **mat2, int row1, int row_col, int col2);
void print_matrixf(float **mat, int row, int col);
float **transposef(float **mat, int row, int col);
void mat_cofactor(float **mat, float *co_mat[], int r_cof, int c_cof, int n);
float det_22_33(float **mat, int n);
float detf(float **mat, int n, int isCofator);
float **mat_adjoint(float **mat, int n);
float **mat_inverse(float **mat, int n);

#endif /* DMATRIX2D_H */
