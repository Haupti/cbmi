#ifndef LEXER_HEADER
#define LEXER_HEADER

#include <stdlib.h>

enum Token {
    INC,
    DEC,
    PRINT,
    NEXT,
    PREV,
    LOOP_START,
    LOOP_END
};


size_t read_tokens(char * program, size_t program_length, enum Token * token_storage);

#endif
