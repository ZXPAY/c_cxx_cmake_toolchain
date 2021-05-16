#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Command example
 *
 * -f 100 200 30 -d 1000 -fs 100
 */

#define F_CMD_START_INDEX (1)
#define F_CMD_INCREMENT   (3)
#define FG_FREQ           (1)
#define FG_SIZE           (2)
#define FG_FS             (3)
#define FREQ_CMD          ("-fq")
#define SIZE_CMD          ("-sz")
#define FS_CMD            ("-fs")
#define PI                (acos(-1))

typedef struct _freq_t {
    int *array;
    int len;
}freq_t;

int getValue(char *data) {
    int val = 0;
    int num = strlen(data);
    int dig;

    for(int i=0;i<num;i++) {
        if(data[i] <= '9' && data[i] >= '0') {  
            dig = 1;
            for(int j=0;j<num-i-1;j++) {
                dig *= 10;
            }
            val += dig * (data[i]-48);
        }
        else {
            return -1;
        }
    }

    return val;
}

int main(int argc, char *argv[]) {
    int flag = 0;
    int data_size = 0;
    int data_fs = 0;
    int temp;

    int *freq_array = (int *)malloc((argc-5)*sizeof(int));
    memset(freq_array, 0, (argc-5)*sizeof(int));

    freq_t freq;
    freq.array =freq_array;
    freq.len = 0;

    for(int i=1;i<argc;i++) {
        //  printf("%d, %s\n", i, argv[i]);
        if(!strcmp(argv[i], FREQ_CMD)) {
            flag = FG_FREQ;
            continue;
        }
        else if(!strcmp(argv[i], SIZE_CMD)) {
            flag = FG_SIZE;
            continue;
        }
        else if(!strcmp(argv[i], FS_CMD)) {
            flag = FG_FS;
            continue;
        }
        if(FG_FREQ == flag) {
            temp = getValue(argv[i]);
            if(temp == -1) {
                printf("Please enter valid frequency number\n");
                return 0;
            }
            freq.array[freq.len++] = temp;
            printf("Freq: %d\n", temp);
        }
        else if(FG_SIZE == flag) {
            temp = getValue(argv[i]);
            if(temp == -1) {
                printf("Please enter valid size number\n");
                return 0;
            }
            data_size = temp;
            printf("Size: %d\n", data_size);
        }
        else if(FG_FS == flag) {
            temp = getValue(argv[i]);
            if(temp == -1) {
                printf("Please enter valid FS (frequency sampling rate)\n");
                return 0;
            }
            data_fs = temp;
            printf("FS: %d\n", data_fs);

        }
    }

    if(data_size == 0 || data_fs == 0 || freq.len == 0) {
        printf("Please enter valid command \n");
        return 0;
    }
    
    printf("Genrerate the sine freq: ");
    for(int i=0;i<freq.len;i++) {
        printf("%d, ", freq.array[i]);
    }
    printf("dots num: %d", data_size);
    printf(", sampling rate: %d\n", data_fs);
    

    float *data = (float *)malloc(sizeof(float)*data_size);

    float temp_sum;
    float delta_t = 1 / (float)data_fs;
    
    char filename[100];
    memset(filename, 0, sizeof(filename));
    sprintf(filename, "sine_%d_%d.txt", data_size, data_fs);
    FILE *f;
    f = fopen(filename, "w");
    fclose(f);
    f = fopen(filename, "a");
    
    for(int k=0;k<data_size;k++) {
        temp_sum = 0;
        for(int j=0;j<freq.len;j++) {
            temp_sum += sinf(2*PI*freq.array[j]*k*delta_t);
        } 
        data[k] = temp_sum;
        printf("%f\n", temp_sum);
        fprintf(f, "%.5f\n", temp_sum);
    }
    
    fclose(f);
    free(freq.array);
    free(data);
    return 0;
}




