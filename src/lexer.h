#ifndef LEXER_HEADER
#define LEXER_HEADER

#include <stdlib.h>

enum TokenType {
    INC,
    DEC,
    PRINT,
    NEXT,
    PREV,
    LOOP_START,
    LOOP_END,
    DEF,
    IDENTIFIER,
    STATEMENT_END,
    IDENTIFIER_REF,
    ASSIGNMENT_OPERATOR
};

typedef struct Token {
    enum TokenType type;
    char * value;
} Token;


size_t read_tokens(char * program, size_t program_length, Token * token_storage);

#endif
