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

void print_matrixf(float *mat[], int row, int col) {
	if(row < 0 || col < 0) {
        return;
    }
	for(int i=0;i<row;i++) {
		for(int j=0;j<col;j++) {
			printf("%.2f, ", mat[i][j]);
		}
		printf("\n");
	}
}

float **transposef(float *mat[], int row, int col) {
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
    free(mat);
	return new_M;
}


float det_22_33(float *mat[], int len) {
	if (len < 0) return 0;
	else if(len == 1) {
		return mat[0][0];
	}
	else if(len == 2) {
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}

	else if(len == 3) {
		int temp_cp, temp_cn, r;
		float det_sum = 0;
		float temp_mulp, temp_muln;
		
		// positive & negative
		int k = 0;
		while(k < len) {
			r = 0;
			temp_mulp = 1.0;
			temp_muln = 1.0;
			for(int i=k ;i<k+len;i++) {
				temp_cp = i;
				if(temp_cp >= len) {
					temp_cp -= len;
				}
				temp_cn = len - temp_cp - 1;
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

void getCofactor(float *mat[], float *co_mat[], int r_cof, int c_cof, int len) {
	int r = 0, c = 0;
	for(int i=0;i<len;i++) {      // row
		for(int j=0;j<len;j++) {  // col
			if(i != r_cof && j != c_cof) {
				co_mat[r][c] = mat[i][j];
				c++;
				if(c == len-1) {
					c = 0;
					r++;
				}
			}
		}
	}
}

static int cnt = 0;
static float **save_free_address[MAX_ITER_DET_MATRIX];

float detf(float *mat[], int n, int isCofator) {
	int D = 0; // Initialize result
 
    if(1 == n) {
        return mat[0][0];
	}
	else if(2 == n) {
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}


	float **mat_cof = create_matrixf(n, n);
	save_free_address[cnt++] = mat_cof;
	
    int sign = 1;
 
    for (int f = 0; f < n; f++) {
        getCofactor(mat, mat_cof, 0, f, n);
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
