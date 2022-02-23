

int input_data[2][14] = {
    {9, 6, 4, 9, 4, 9, 10, 8, 10, 9, 4, 8, 6, 3},
    {4, 4, 10, 10, 5, 5, 5, 5, 8, 8, 8, 5, 10, 4}
};



int main() {

    for(int i=0;i<14;i++) {
        printf("%d, %d\n", input_data[0][i], input_data[1][i]);
    }

    return 0;
}
