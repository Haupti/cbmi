#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER

#include "lexer.h"

int findMatchingClose(int open_bracket_pos, Token * program, int tokens_length);
int findMatchingOpen(int close_bracket_pos, Token * program, int tokens_length);
int interpret(int token_count, Token * program_tokens);

#endif
