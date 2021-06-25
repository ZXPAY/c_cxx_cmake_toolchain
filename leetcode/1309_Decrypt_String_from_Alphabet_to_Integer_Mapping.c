#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
Given a string s formed by digits ('0' - '9') and '#' . We want to map s to English lowercase characters as follows:

Characters ('a' to 'i') are represented by ('1' to '9') respectively.
Characters ('j' to 'z') are represented by ('10#' to '26#') respectively. 
Return the string formed after mapping.

It's guaranteed that a unique mapping will always exist.
*/


// char test_string[] = "10#11#12";
// char test_string[] = "12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#";
char test_string[] = "912#19#26#819#1722#219#19#10#10#26#74422#21#12#26#1923#10#23#24#4113#11#13#121#12#15#22#5313#21#16#10#36215#23#24#22#211#22#420#20#10#18#16#15#215#15#17#16#15#21#26#11#22#519#22#773314#1319#11#24#911#23#620#315#19#23#513#13#13#21#212#15#220#22#61519#22#21#22#14#24#610#24#13#16#110#22#26#24#16#110#23#718811#18#8910#25#12#11#14#2725#15#21#26#21#22#4719#217#23#516#23#220#17#8821#1921#413#26#22#510#25#19#310#19#514#19#3320#10#17#920#319#10#116#23#11#314#17#18#11#15#13#23#111464713#12#17#26#23#8424#6117#615#25#521#15#119#2823#15#25#25#22#23#13#1712#17#20#16#611#1413#10#513#20#13#13#22#523#16#17#720#14#23#710#18#10#11#22#11#42714#25#126#9913#12#15#19#7811#18#516#810#14#112#21#15#18#71719#25#12#18#410#20#112#23#20#1120#24#16#911#13#3212#411#26#225#825#14#18#26#3916#981724#";

char *freqAlphabets(char *s){
    int char_len = strlen(s);
    char *decode_str = (char *)malloc(sizeof(char) * char_len);
    int sv_cnt = 0;
    memset(decode_str, 0, sizeof(char) * char_len);
    uint8_t temp[3], cnt = 0;
    int flag = 0;
    for(int i=0;i<char_len;i++) {
        if(i+2 < char_len) {
            if(s[i+2] == '#') {
                flag = 1;
            }
        }
        // #, j~z
        if(flag == 1) {
            temp[cnt] = s[i];
            // printf("1=>%c\n", s[i]);
        }
        // a~i
        else {
            // printf("0=>%c\n", s[i]);
            temp[0] = s[i];
        }
        
        cnt++;
        if(3 == cnt && 1 == flag) {
            // printf("out1: %c\n", (temp[0]-48)*10 + (temp[1]-48) - 10 + 'j');
            decode_str[sv_cnt++] = (char)((temp[0]-48)*10 + (temp[1]-48) - 10 + 'j');
            flag = 0;
            cnt = 0;
        }
        else if(0 == flag) { // flag = 0
            // printf("out0: %c\n", temp[0] - 48 -1 + 'a');
            decode_str[sv_cnt++] = (char)(temp[0] - 48 -1 + 'a');
            cnt = 0;
        }
    }
    
    return decode_str;
}

int main() {
    printf("start\n");

    printf("minOperations: %s\n", freqAlphabets(test_string));

}
