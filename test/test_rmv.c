#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rmv.h"

#define WINDOW_SIZE 4

float x_buf[WINDOW_SIZE];

int main(void) {
    memset(x_buf, 5, sizeof(float)*WINDOW_SIZE);

    printf("start, generate the test data\n");
    float test_x[100];
    float test_y[100];
    memset(test_x, 0, sizeof(float)*100);
    memset(test_y, 0, sizeof(float)*100);
    
    for(int i=0;i<100;i++) {
        if(i<20) {
            test_x[i] = 5;
        }
        else if(i<50) {
            test_x[i] = 10;
        }
        else if(i<80) {
            test_x[i] = 20;
        }
        else {
            test_x[i] = 10;
        }
    }

    rmv_t test_rmv;
    init_rmv(&test_rmv, x_buf, WINDOW_SIZE);
    for(int k=0;k<100;k++) {
        test_y[k] = iter_rmv(&test_rmv, test_x[k]);
    }

    for(int k=0;k<100;k++) {
        printf("%.2f, %.2f\n", test_x[k], test_y[k]);
    }

    printf("end\n");
    return 0;
}



