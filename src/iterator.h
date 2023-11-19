#ifndef ITERATOR_HEADER
#define ITERATOR_HEADER

#include <stdlib.h>
#include "lexer.h"

typedef struct TokenIterator {
    Token * arr;
    size_t arr_len;
    int position;
} TokenIterator;

Token next_token(TokenIterator * it);
Token start_iterator(TokenIterator * it);
TokenIterator token_iterator(Token * arr, size_t length);
int has_next(TokenIterator * it);
void go_to_position(TokenIterator * it, int pos);

#endif
