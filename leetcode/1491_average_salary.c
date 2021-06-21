#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Given an array of unique integers salary where salary[i] is the salary of the employee i.

Return the average salary of employees excluding the minimum and maximum salary.
*/

int test_salary[] = {4000,3000,1000,2000};   // answer should be 2500


double average(int *salary, int salarySize){
    double temp_sum = 0;
    int temp_max = 0, temp_min = 0;
    for(int i=0;i<salarySize;i++) {
        if(i == 0) {
            temp_max = temp_min = salary[0];
        }
        if(temp_max < salary[i]) temp_max = salary[i];
        if(temp_min > salary[i]) temp_min = salary[i];
        temp_sum += salary[i];
    }
    temp_sum -= temp_max + temp_min;
    return temp_sum / (double) (salarySize - 2);
}

int main() {
    printf("start\n");

    printf("average salary: %.4f\n", average(test_salary, sizeof(test_salary)/sizeof(int)));

}
