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
    ASSIGNMENT_OPERATOR,
    READ_INPUT
};

typedef struct Token {
    enum TokenType type;
    char * value;
} Token;


size_t read_tokens(char * program, size_t program_length, Token * token_storage);

void print_token(Token token);
void print_tokens(Token * tokens, size_t token_count);

#endif
