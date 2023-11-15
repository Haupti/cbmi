#include "lexer.h"

// returns the positive index of the closing bracket in the program tokens if it is found.
// if it cannot find it, returns -1 (error case, should not be possible);
int findMatchingClose(int open_bracket_pos,enum Token * program, int tokens_length){
    int loop_acc = 0;

    for(int i = open_bracket_pos + 1; i< tokens_length; i++){
        enum Token ct = program[i];
        switch (ct) {
            case LOOP_START:
                loop_acc += 1;
                break;
            case LOOP_END:
                if(loop_acc == 0){
                    return i;
                } else {
                    loop_acc -= 1;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}

// returns the positive index of the opening bracket in the program tokens if it is found.
// if it cannot find it, returns -1 (error case, should not be possible);
int findMatchingOpen(int close_bracket_pos, enum Token * program, int tokens_length){
    int loop_acc = 0;

    int i;
    for(i = close_bracket_pos - 1; i >= 0; i--){
        enum Token ct = program[i];
        switch (ct) {
            case LOOP_END:
                loop_acc += 1;
                break;
            case LOOP_START:
                if(loop_acc == 0){
                    return i;
                } else {
                    loop_acc -= 1;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}
