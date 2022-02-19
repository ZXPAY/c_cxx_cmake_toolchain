#include <stdio.h>

void recursive_for(int i_st, int length) {
    if(i_st >= length) return;


    printf("%d\n", i_st);

    recursive_for(i_st + 1, length);
}

int main() {
    recursive_for(0, 20);
}
