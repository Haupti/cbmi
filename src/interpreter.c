#include "iterator.h"
#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    int tokens_len;
} Identifier;

void exec_sub(Identifier variable, char * current_byte, char * bytes){
    TokenIterator it = token_iterator(variable.tokens, variable.tokens_len);

    Token token = start_iterator(&it);
    while(has_next(&it)){
        switch(token.type){
                case INC:
                    bytes[*current_byte] += 1;
                    break;
                case DEC:
                    bytes[*current_byte] -= 1;
                    break;
                case NEXT:
                    *current_byte += 1;
                    break;
                case PREV:
                    *current_byte -= 1;
                    break;
                case PRINT:
                    printf("%c", bytes[*current_byte]);
                    break;
                case LOOP_START:
                    if(bytes[*current_byte] == 0){
                        int close_cmd = findMatchingClose(it.position, variable.tokens, variable.tokens_len);
                        if(close_cmd == -1){
                            printf("error: no closing bracket found\n");
                            exit(EXIT_FAILURE);
                        }
                        go_to_position(&it, close_cmd-1);
                    }
                    break;
                case LOOP_END:
                    if(bytes[*current_byte] != 0){
                        int open_cmd = findMatchingOpen(it.position, variable.tokens, variable.tokens_len);
                        if(open_cmd == -1){
                            printf("error: no opening bracket found\n");
                            exit(EXIT_FAILURE);
                        }
                        go_to_position(&it, open_cmd-1);
                    }
                    break;
                default:
                    printf("error in subroutine: on token %d token not allowed here\n", it.position);
                    exit(EXIT_FAILURE);
                    break;
        }
        token = next_token(&it);
    }
}

Identifier read_identifier_and_jump_to_statement_end(TokenIterator * it){
    if(!has_next(it)){
        printf("error: at token %d. identifier expected\n", it->position);
        exit(EXIT_FAILURE);
    }
    Token id_token = next_token(it);
    if(id_token.type != IDENTIFIER){
        printf("error: at token %d. identifier expected\n", it->position);
        exit(EXIT_FAILURE);
    }

    if(!has_next(it)){
        printf("error: at token %d. assignment expected\n", it->position);
        exit(EXIT_FAILURE);
    }
    Token assignment_token = next_token(it);
    if(assignment_token.type != ASSIGNMENT_OPERATOR){
        printf("error: at token %d. assignment expected\n", it->position);
        exit(EXIT_FAILURE);
    }

    if(!has_next(it)){
        printf("error: at token %d. end of statement token expected\n", it->position);
        exit(EXIT_FAILURE);
    }

    Token * variable_tokens = malloc(10000 * sizeof(Token));
    // TODO marwin: reduce size to what is needed after completing read
    int variable_tokens_count = 0;
    Token token = next_token(it);
    int end_reached = 0;
    while(has_next(it) && end_reached == 0){
        if(token.type == INC
            || token.type == DEC
            || token.type == NEXT
            || token.type == PREV
            || token.type == PRINT
            || token.type == LOOP_END
            || token.type == LOOP_START
        ){
            variable_tokens[variable_tokens_count] = token;
            variable_tokens_count += 1;
        } else if(token.type == STATEMENT_END){
            end_reached = 1;
            break;
        } else {
            printf("error: at token %d unexpected token within variable assignment\n", it->position);
            exit(EXIT_FAILURE);
        }
        token = next_token(it);
    }
    Identifier variable = {id_token.value, variable_tokens, variable_tokens_count};
    return variable;
}

int interpret(int token_count, Token * program_tokens){
    Identifier variables[10000];
    int variable_count = 0;

    // set all bytes to zero
    char bytes[10];
    for(int i = 0; i < 10; i++){
        bytes[i] = '\0';
    }

    char current_byte = 0;

    TokenIterator it = token_iterator(program_tokens, token_count);

    Token token = start_iterator(&it);
    while(has_next(&it)){
        if(current_byte >= 10 || current_byte < 0){
            printf("error: at token %d. byte is not available for program", it.position);
            return EXIT_FAILURE;
        }
        switch(token.type) {
            case DEF:
                variables[variable_count] = read_identifier_and_jump_to_statement_end(&it);
                variable_count += 1;
                token = current_token(&it);
                break;
            case IDENTIFIER:
                printf("error: at token %d. identifier without use or assignment\n",it.position);
                return EXIT_FAILURE;
                break;
            case STATEMENT_END:
                printf("error: at token %d. no statement to end\n",it.position);
                return EXIT_FAILURE;
                break;
            case ASSIGNMENT_OPERATOR:
                printf("error: at token %d. assignment operator without anything to assign\n",it.position);
                return EXIT_FAILURE;
                break;
            case IDENTIFIER_REF:
                if(!has_next(&it)){
                    printf("error: at token %d. unexpected end. identifier expected after reference operator\n",it.position);
                    return EXIT_FAILURE;
                }
                token = next_token(&it);
                int found_variable = 0;
                for(int var = 0; var < variable_count; var++){
                    if(strcmp(variables[var].name,token.value) == 0){
                        found_variable = 1;
                        exec_sub(variables[var], &current_byte, bytes);
                        break;
                    }
                }
                if(found_variable != 1){
                    printf("error: at token %d.identifier not known\n", it.position);
                }
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
                    int close_cmd = findMatchingClose(it.position, program_tokens, token_count);
                    if(close_cmd == -1){
                        printf("error: no closing bracket found\n");
                        return EXIT_FAILURE;
                    }
                    go_to_position(&it, close_cmd-1); // go to the command before becasue next_token will be called before next iteration
                }
                break;
            case LOOP_END:
                if(bytes[current_byte] != 0){
                    int open_cmd = findMatchingOpen(it.position, program_tokens, token_count);
                    if(open_cmd == -1){
                        printf("error: no opening bracket found\n");
                        return EXIT_FAILURE;
                    }
                    go_to_position(&it, open_cmd-1); // go to the command before because next_token will be called before next iteration
                }
                break;
        }
        token = next_token(&it);

    }
    return EXIT_SUCCESS;
}
