#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/lexer.h"
#include "src/interpreter.h"

char * program_str = "+++++[>+++++++<-]>.";
//                    01234567890123456789


int main(){
    enum Token * programm_tokens = malloc(500 * sizeof(enum Token));
    size_t program_length = strlen(program_str);

    size_t token_count = read_tokens(program_str, program_length, programm_tokens);

    printf("exec program\n");
    // set all bytes to zero
    char bytes[10];
    for(int i = 0; i < 10; i++){
        bytes[i] = '\0';
    }

    char current_byte = 0;
    int cmd = 0;
    for(cmd = 0; cmd < token_count; cmd++){
        enum Token token = programm_tokens[cmd];
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
                    int close_cmd = findMatchingClose(cmd, programm_tokens, token_count);
                    if(close_cmd == -1){
                        printf("error: no closing bracket found");
                        exit(EXIT_FAILURE);
                    }
                    cmd = close_cmd;
                }
                break;
            case LOOP_END:
                if(bytes[current_byte] != 0){
                    int open_cmd = findMatchingOpen(cmd, programm_tokens, token_count);
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
