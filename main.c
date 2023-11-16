#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/lexer.h"
#include "src/interpreter.h"

char * program_str = "+++++[>++++++++<-]>.";
//                    01234567890123456789


int main(int args, char * argv[]){

    enum Token * programm_tokens = malloc(500 * sizeof(enum Token));
    size_t program_length = strlen(program_str);

    size_t token_count = read_tokens(program_str, program_length, programm_tokens);
    return interpret(token_count, programm_tokens);
}
