#include <stdio.h>

int input_data[2][14] = {
    {9, 6, 4, 9, 4, 9, 10, 8, 10, 9, 4, 8, 6, 3},
    {4, 4, 10, 10, 5, 5, 5, 5, 8, 8, 8, 5, 10, 4}
};


void f(int x, int index, int *result) {
    printf("= %d, %d\n", x, *result);
    *result += x;
    if(x >= 106) {
        return;
    }
    f(x+index, index+1, result);
}


int main() {

    // for(int i=0;i<14;i++) {
    //     printf("%d, %d\n", input_data[0][i], input_data[1][i]);
    // }

    int x = 1;
    int sum = 0;
    for(int i=1;x<=106;i++) {
        printf("[%d]: %d, %d\n", i-1, x, sum);
        sum += x;
        x += i;
    }

    int i = 1;
    while(x<=106) {

        x += i;
        sum += x;

        i++;
    }
    printf("sum: %d\n", sum);

    int sss = 0;
    f(1, 1, &sss);
    printf("%d\n", sss);

    return 0;
}
