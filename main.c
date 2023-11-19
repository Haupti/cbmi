#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/lexer.h"
#include "src/interpreter.h"
#include "src/fileio.h"
#include "src/iterator.h"


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

    //print_tokens(programm_tokens, token_count);
    return interpret(token_count, programm_tokens);
}

