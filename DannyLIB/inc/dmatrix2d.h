#ifndef DMATRIX2D_H
#define DMATRIX2D_H

#define MAX_ITER_DET_MATRIX  20

float **create_matrixf(int row, int col);
void delete_matrixf(float **mat);
void print_matrixf(float *mat[], int row, int col);
float **transposef(float *mat[], int row, int col);
void getCofactor(float *mat[], float *co_mat[], int r_cof, int c_cof, int len);
float det_22_33(float *mat[], int len);
float detf(float *mat[], int n, int isCofator);

#endif /* DMATRIX2D_H */
