#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "src/lexer.h"
#include "src/interpreter.h"

int read_file(char * filename, char * target, int max_bytes){
    size_t size_tracker = 0;
    FILE * fptr;
    fptr = fopen(filename, "r");
    char line[200];
    while(fgets(line, 200, fptr) != NULL){
        if(size_tracker + strlen(line) > max_bytes){
            return -1;
        }
        size_tracker += strlen(line);
        strcat(target, line);
    }
    fclose(fptr);
    return 0;
}

void print_tokens(Token * tokens, size_t token_count){
    for(int i = 0; i < token_count; i++){
        Token token = tokens[i];
        switch(token.type){
            case DEF:
                printf("DEF\n");
                break;
            case DEC:
                printf("DEC\n");
                break;
            case STATEMENT_END:
                printf("STATEMENT_END\n");
                break;
            case ASSIGNMENT_OPERATOR:
                printf("ASSIGNMENT_OPERATOR\n");
                break;
            case INC:
                printf("INC\n");
                break;
            case PRINT:
                printf("PRINT\n");
                break;
            case NEXT:
                printf("NEXT\n");
                break;
            case PREV:
                printf("PREV\n");
                break;
            case LOOP_END:
                printf("LOOP_END\n");
                break;
            case LOOP_START:
                printf("LOOP_START\n");
                break;
            case IDENTIFIER:
                printf("IDENTIFIER=%s\n",token.value);
                break;
            case IDENTIFIER_REF:
                printf("IDENTIFIER_REF\n");
                break;
        }
    }
}

int main(int args, char * argv[]){

    if(args <= 1){
        puts("no arguments supplied, exiting");
        exit(EXIT_SUCCESS);
    }
    if(args > 2){
        puts("too may arguments");
        exit(EXIT_FAILURE);
    }
    char * arg = argv[1];

    if(strcmp(arg, "--help") == 0){
        puts("--help prints this");
        puts("--info supplied file property infos");
        puts("<filename> file to interpret");
        exit(EXIT_SUCCESS);
    }

    if(strcmp(arg, "--info") == 0){
        puts("max file size is 9999 chars, max line length is 199 chars.");
        return EXIT_SUCCESS;
    }

    if(access(arg, F_OK) != 0){
        puts("cannot open file, does it exist?");
        return EXIT_FAILURE;
    }

    char file_content[10000] = "";
    int status = read_file(arg, file_content, 10000);
    if(status == -1){
        puts("error while reading file: file too long, see --info");
        exit(EXIT_FAILURE);
    }

    Token * programm_tokens = malloc(10000 * sizeof(Token));
    size_t program_length = strlen(file_content);

    size_t token_count = read_tokens(file_content, program_length, programm_tokens);
    print_tokens(programm_tokens, token_count);
    //return interpret(token_count, programm_tokens);
}

