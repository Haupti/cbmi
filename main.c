#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/lexer.h"

char * program_str = "+++++++++++++++++++++++++++++++++.>+++++++++++++++++++++++++++++++++.";


int main(){
    enum Token * programm_tokens = malloc(500 * sizeof(enum Token));
    size_t program_length = strlen(program_str);

    size_t token_count = read_tokens(program_str, program_length, programm_tokens);

    printf("exec program\n");
    char bytes[3] = {'\0', '\0', '\0'};
    char current_byte = 0;
    for(int i = 0; i < token_count; i++){
        enum Token token = programm_tokens[i];
        if(token == INC){
            bytes[current_byte] += 1;
        }
        if(token == DEC){
            bytes[current_byte] -= 1;
        }
        if(token == NEXT){
            current_byte += 1;
        }
        if(token == PRINT){
           printf("%s", bytes);
        }
    }

    return EXIT_SUCCESS;
}
