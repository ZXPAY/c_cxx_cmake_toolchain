#include <stdio.h>
#include "add.h"

int arg1[] = {-1, 2, 5};
int arg2[] = {5, 7, -10};
int ans[] = {4, 9, -5};

int main(void) {
  int data_length = sizeof(arg1)/sizeof(int);
  int cnt = 0;
  for(int i=0;i<data_length;i++) {
    if(add(arg1[i], arg2[i]) == ans[i]) {
      cnt++;
    }
  }
  if(cnt == data_length) {
    printf("test [add] function success\n");
  }
  else {
    printf("test [add] function fail"); 
  }
}




