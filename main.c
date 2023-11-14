#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/lexer.h"

char * program_str = "+++++++++++++++++++++++++++++++++."; // prints "!"


int main(){
    enum Token * programm_tokens = malloc(50 * sizeof(enum Token));
    size_t program_length = strlen(program_str);

    read_tokens(program_str, program_length, programm_tokens);
    return EXIT_SUCCESS;
}
