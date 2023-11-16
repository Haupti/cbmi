#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

// returns the positive index of the closing bracket in the program tokens if it is found.
// if it cannot find it, returns -1 (error case, should not happen);
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
// if it cannot find it, returns -1 (error case, should not happen);
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


int interpret(int token_count, enum Token * program_tokens){
    // set all bytes to zero
    char bytes[10];
    for(int i = 0; i < 10; i++){
        bytes[i] = '\0';
    }

    char current_byte = 0;
    int cmd = 0;
    for(cmd = 0; cmd < token_count; cmd++){
        enum Token token = program_tokens[cmd];
        switch (token) {
            case INC:
                bytes[current_byte] += 1;
                break;
            case DEC:
                bytes[current_byte] -= 1;
                break;
            case NEXT:
                current_byte += 1;
                break;
            case PREV:
                current_byte -= 1;
                break;
            case PRINT:
                printf("%c", bytes[current_byte]);
                break;
            case LOOP_START:
                if(bytes[current_byte] == 0){
                    int close_cmd = findMatchingClose(cmd, program_tokens, token_count);
                    if(close_cmd == -1){
                        printf("error: no closing bracket found");
                        exit(EXIT_FAILURE);
                    }
                    cmd = close_cmd;
                }
                break;
            case LOOP_END:
                if(bytes[current_byte] != 0){
                    int open_cmd = findMatchingOpen(cmd, program_tokens, token_count);
                    if(open_cmd == -1){
                        printf("error: no opening bracket found");
                        exit(EXIT_FAILURE);
                    }
                    cmd = open_cmd;
                }
                break;
       }
    }
    return EXIT_SUCCESS;
}
