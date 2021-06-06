#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "dmatrix2d.h"

float **create_matrixf(int row, int col) {
	float **mat = (float **)malloc(sizeof(float *)*row);
    for(int i=0;i<row;i++) {
        mat[i] = (float *)malloc(sizeof(float)*col);
    }
	return mat;
}

void delete_matrixf(float **mat) {
	free(mat);
}

float **mat_mul(float **mat1, float **mat2, int row1, int row_col, int col2) {
	float **mat = create_matrixf(row1, col2);
	for(int i=0;i<row1;i++) {
		for(int j=0;j<col2;j++) {
			float temp_sum = 0;
			for(int k=0;k<row_col;k++) {
				temp_sum += mat1[i][k] * mat2[k][j];
			}
			mat[i][j] = temp_sum;
		}
	}
	return mat;
}

void print_matrixf(float **mat, int row, int col) {
	if(row < 0 || col < 0) {
        return;
    }
	for(int i=0;i<row;i++) {
		for(int j=0;j<col;j++) {
			printf("%.4f, ", mat[i][j]);
		}
		printf("\n");
	}
}

float **transposef(float **mat, int row, int col) {
    if(row < 0 || col < 0) {
        return 0;
    }
	int new_r = col;
	int new_c = row;
	float **new_M = (float **)malloc(new_r * sizeof(float *));
    for(int i=0;i<new_r;i++) {
        new_M[i] = (float *)malloc(sizeof(float)*new_c);
    }
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++) {
            new_M[j][i] = mat[i][j];
        }
    }
	return new_M;
}


float det_22_33(float **mat, int n) {
	if (n < 0) return 0;
	else if(n == 1) {
		return mat[0][0];
	}
	else if(n == 2) {
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}

	else if(n == 3) {
		int temp_cp, temp_cn, r;
		float det_sum = 0;
		float temp_mulp, temp_muln;
		
		// positive & negative
		int k = 0;
		while(k < n) {
			r = 0;
			temp_mulp = 1.0;
			temp_muln = 1.0;
			for(int i=k ;i<k+n;i++) {
				temp_cp = i;
				if(temp_cp >= n) {
					temp_cp -= n;
				}
				temp_cn = n - temp_cp - 1;
				temp_mulp *= mat[r][temp_cp];
				temp_muln *= mat[r][temp_cn];
				r++;
			}
			det_sum += (temp_mulp - temp_muln);
			k++;
		}
		return det_sum;
	}
	else {
		return 0;
	}

}

void mat_cofactor(float **mat, float **co_mat, int r_cof, int c_cof, int n) {
	int r = 0, c = 0;
	for(int i=0;i<n;i++) {      // row
		for(int j=0;j<n;j++) {  // col
			if(i != r_cof && j != c_cof) {
				co_mat[r][c] = mat[i][j];
				c++;
				if(c == n-1) {
					c = 0;
					r++;
				}
			}
		}
	}
}

static int cnt = 0;
static float **save_free_address[MAX_ITER_DET_MATRIX];

float detf(float **mat, int n, int isCofator) {
	int D = 0; // Initialize result
 
    if(1 == n) {
        return mat[0][0];
	}
	else if(2 == n) {
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}


	float **mat_cof = create_matrixf(n-1, n-1);
	save_free_address[cnt++] = mat_cof;
	
    int sign = 1;
 
    for (int f = 0; f < n; f++) {
        mat_cofactor(mat, mat_cof, 0, f, n);
        D += sign * mat[0][f] * detf(mat_cof, n - 1, true);

        sign = -sign;
    }

	assert(cnt<MAX_ITER_DET_MATRIX);
	if(!isCofator) {
		int temp_cnt = cnt;
		for(int i=0;i<temp_cnt;i++) {
			delete_matrixf(save_free_address[i]);
			cnt--;
		}
	}
    return D;
}

float **mat_adjoint(float **mat, int n) {
    assert(n > 1);

	float **mat_adj = create_matrixf(n, n);
	float **temp_conf = create_matrixf(n-1, n-1);
	float sign = 1;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			mat_cofactor(mat, temp_conf, i, j, n);
			mat_adj[i][j] = detf(temp_conf, n-1, false) * sign;
			sign *= -1;
		}
	}

	return mat_adj;
}

float **mat_inverse(float **mat, int n) {
    assert(n > 1);
	float det_val = detf(mat, n, false);
	float **mat_inv = mat_adjoint(mat, n);
	mat_inv = transposef(mat_inv, n, n);
	float det_val_inv = 1 / det_val;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			mat_inv[i][j] *= det_val_inv;
		}
	}
	return mat_inv;
}
