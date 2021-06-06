#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dmatrix2d.h"

#define TEST_NUM  100

float test_func(float x) {
    return 1.2*x + 0.13;
}


int main() {
    printf("test identify a line y = 1.2x + 0.13\n");

    // Generate the x and y
    float **y = create_matrixf(TEST_NUM, 1);
    float **x = create_matrixf(TEST_NUM, 2);
    
    for(int i=0;i<TEST_NUM;i++) {
        x[i][0] = (float)i *0.1 + 0.1;
        x[i][1] = 1.0;
        y[i][0] = test_func(x[i][0]) + (rand() % 100) / 100000.0;
    }
    
    float **xT = transposef(x, TEST_NUM, 2);
    float **x_xT = mat_mul(xT, x, 2, TEST_NUM, 2);

    float **x_xT_inv = mat_inverse(x_xT, 2);
    float **x_xT_inv_xT = mat_mul(x_xT_inv, xT, 2, 2, TEST_NUM);
    float **para = mat_mul(x_xT_inv_xT, y, 2, TEST_NUM, 1);

    print_matrixf(para, 2, 1);

}
