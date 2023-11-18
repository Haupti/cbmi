#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

// returns the positive index of the closing bracket in the program tokens if it is found.
// if it cannot find it, returns -1 (error case, should not happen);
int findMatchingClose(int open_bracket_pos,Token * program, int tokens_length){
    int loop_acc = 0;

    for(int i = open_bracket_pos + 1; i< tokens_length; i++){
        Token ct = program[i];
        switch (ct.type) {
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
int findMatchingOpen(int close_bracket_pos, Token * program, int tokens_length){
    int loop_acc = 0;

    int i;
    for(i = close_bracket_pos - 1; i >= 0; i--){
        Token ct = program[i];
        switch (ct.type) {
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

typedef struct Identifier {
    char * name;
    Token * tokens;
} Identifier;

int interpret(int token_count, Token * program_tokens){
    Identifier variables[10000];
    int variable_count = 0;

    // set all bytes to zero
    char bytes[10];
    for(int i = 0; i < 10; i++){
        bytes[i] = '\0';
    }

    char current_byte = 0;
    int cmd = 0;
    for(cmd = 0; cmd < token_count; cmd++){
        Token token = program_tokens[cmd];
        enum TokenType tokenType = token.type;
        switch (tokenType) {
            case DEF:
                /*if(token_count <= cmd+1 && program_tokens[cmd + 1].type == IDENTIFIER){
                    int id_token_count = 0;
                    // TODO marwin: this is too much to
                    Token id_tokens[10000];
                    while(token_count >= cmd + 1 + id_token_count){
                        int current = cmd + 1 + id_token_count;
                        if(is_allowed_in_variable(program_tokens[current])){
                            id_tokens[id_token_count] = program_tokens[current];
                            id_token_count += 1;
                        }
                        if(program_tokens[current].type == STATEMENT_END){
                            id_token_count += 1;
                            break;
                        }
                        else {
                            printf("error while interpreting variable\nonly operations are allowed to be assigned to a variable\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    Token * saved_tokens = malloc((id_token_count - 1) * sizeof(Token));

                    Identifier id = { token.value, id_tokens };
                    variables[variable_count] = id;
                }
                */
                break;
            case IDENTIFIER:
                // TODO marwin
                break;
            case STATEMENT_END:
                // TODO marwin
                break;
            case ASSIGNMENT_OPERATOR:
                // TODO marwin
                break;
            case IDENTIFIER_REF:
                // TODO marwin
                break;
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
