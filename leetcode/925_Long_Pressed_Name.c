#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/* true */
// char test_name[] = "alex";
// char test_typed[] = "aaleexxx";

/* false */
// char test_name[] = "saeed";
// char test_typed[] = "ssaaedd";

/* false */
// char test_name[] = "saeed";
// char test_typed[] = "ssaaeedddddld";

/* false */
char test_name[] = "alex";
char test_typed[] = "aaleelx";

/*
Your friend is typing his name into a keyboard. Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.

You examine the typed characters of the keyboard. Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.
*/

bool isLongPressedName(char *name, char *typed){
    int length = strlen(name);
    int length_typed = strlen(typed);
    int i_type = 0;;
    for(int i=0;i<length;i++) {
        while(name[i] != typed[i_type++]) {
            if(i == 0) return false;
            if(i > 0) {
                if(typed[i_type-1] != name[i-1]) return false;
            }
            if(i_type >= length_typed) return false;
        }
    }

    if(i_type < length_typed) {
        while(i_type < length_typed) {
            if(name[length-1] != typed[i_type++]) return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }


    bool result = isLongPressedName(test_name, test_typed);
    if(result) printf("true\n");
    else       printf("false\n");

}

