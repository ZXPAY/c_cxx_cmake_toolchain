#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
There is a robot starting at position (0, 0), the origin, on a 2D plane. Given a sequence of its moves, judge if this robot ends up at (0, 0) after it completes its moves.

The move sequence is represented by a string, and the character moves[i] represents its ith move. Valid moves are R (right), L (left), U (up), and D (down). If the robot returns to the origin after it finishes all of its moves, return true. Otherwise, return false.

Note: The way that the robot is "facing" is irrelevant. "R" will always make the robot move to the right once, "L" will always make it move left, etc. Also, assume that the magnitude of the robot's movement is the same for each move.
*/

char test_move[] = "LDRRLRUULR";

bool judgeCircle(char *moves){
    int x_cnt = 0;
    int y_cnt = 0;
    int str_len = strlen(moves);
    for(int i=0;i<str_len;i++) {
        if('U' == moves[i]) {
            y_cnt++;
        }
        else if('D' == moves[i]) {
            y_cnt--;
        }
        else if('L' == moves[i]) {
            x_cnt--;
        }
        else if('R' == moves[i]) {
            x_cnt++;
        }
    }
    if(0 == x_cnt && 0 == y_cnt) return 1;
    return 0;
}

int main() {
    printf("start\n");

    printf("judgeCircle: %d\n", judgeCircle(test_move));

}
