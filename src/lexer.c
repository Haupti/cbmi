#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int is_identifier_part(char sym) {
    return (90 >= sym && sym >= 65) || (122 >= sym && sym >= 97) || sym == 95;
}

size_t read_tokens(char * program, size_t program_length, Token * token_storage){
    int token_index = 0;
    int i;
    for(i = 0; i < program_length; i++){
        char sym = program[i];
        if(sym == '+'){
            Token token = { INC, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '-'){
            Token token = { DEC, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '.'){
            Token token = { PRINT, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '>'){
            Token token = { NEXT, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '<'){
            Token token = { PREV, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '['){
            Token token = { LOOP_START, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == ']'){
            Token token = { LOOP_END, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '='){
            Token token = { ASSIGNMENT_OPERATOR, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == ';'){
            Token token = { STATEMENT_END, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == '*'){
            Token token = { IDENTIFIER_REF, NULL};
            token_storage[token_index] = token;
            token_index += 1;
            continue;
        }
        if(sym == ' '){
            continue;
        }
        if(sym == '\n'){
            continue;
        }
        if(i == 0 || (i > 0 && program[i-1] == '\n')){
            if(i+3 <= program_length && program[i] == 'd' && program[i+1] == 'e' && program[i+2] == 'f' && program[i+3] == ' ') {
                Token token = { DEF, NULL};
                token_storage[token_index] = token;
                token_index += 1;
                i+=3;
                continue;
            }
        }
        if(is_identifier_part(sym)){
            const int identifier_max = 9;
            char * identifier = malloc(identifier_max+1 * sizeof(char));
            int identifier_counter = 0;
            while(i+identifier_counter <= program_length && is_identifier_part(program[i+identifier_counter])){
                if(identifier_counter == identifier_max){
                    printf("error while parsing at position %d: identifier too long\nallowed are %d characters\n", i, identifier_max);
                    exit(EXIT_FAILURE);
                }
                identifier[identifier_counter]= program[i+identifier_counter];
                identifier_counter += 1;
            }
            identifier[identifier_counter+1] = '\0';
            Token token = { IDENTIFIER, identifier };
            token_storage[token_index] = token;
            token_index += 1;

            if(identifier_counter == 0){
                continue;
            }else{
                i = i + (identifier_counter - 1);
                continue;
            }
        }
        // otherwise ignore

    }

    return token_index;
}

