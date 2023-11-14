#include <stdlib.h>
#include "lexer.h"

void read_tokens(char * program, size_t program_length, enum Token * token_storage){
    int token_index = 0;
    for(int i = 0; i < program_length; i++){
        char sym = program[i];
        if(sym == '+'){
            token_storage[token_index] = INC;
            token_index += 1;
        }
        if(sym == '-'){
            token_storage[token_index] = DEC;
            token_index += 1;
        }
        if(sym == '.'){
            token_storage[token_index] = PRINT;
            token_index += 1;
        }
    }
}
