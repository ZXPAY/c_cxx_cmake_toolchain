#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char test_current[] = "02:30";
char test_correct[] = "04:35";

typedef struct {
    int8_t hours;
    int8_t minutes;
} mytime_t;

void parse_time(char *time_string, mytime_t *mytime) {
    assert(strlen(time_string)==5);
    mytime->hours = (time_string[0]-'0')*10 + (time_string[1]-'0');
    mytime->minutes = (time_string[3]-'0')*10 + (time_string[4]-'0');
}

int convertTime(char *current, char *correct) {
    mytime_t t_cur, t_cor;
    parse_time(current, &t_cur);
    parse_time(correct, &t_cor);

    // printf("%d:%d, %d:%d\n", t_cur.hours, t_cur.minutes, t_cor.hours, t_cor.minutes);

    /* count hours */
    int count = t_cor.hours - t_cur.hours;
    if(count < 0) count += 24;

    /* count minutes */
    int m = t_cor.minutes - t_cur.minutes;
    if(m < 0) {
        count--;
        m += 60;
    }
    // count the 15 or 5 minutes
    count += m/15;
    m %= 15;
    count += m/5;
    m %= 5;
    count += m;

    return count;
}


int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    printf("result: %d\n", convertTime(test_current, test_correct));


}

