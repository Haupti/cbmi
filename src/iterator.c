#include <stdlib.h>
#include <stdio.h>

#include "iterator.h"


Token next_token(TokenIterator * it){
    if(it->arr_len < (it->position + 1)){
        puts("index out of bounds");
        exit(EXIT_FAILURE);
    }
    it->position += 1;
    return it->arr[(it->position)];
}


TokenIterator token_iterator(Token * arr, size_t length){
    TokenIterator it = {arr, length, 0};
    return it;
}

int has_next(TokenIterator * it){
    return (it->position < (int) it->arr_len);
}

void go_to_position(TokenIterator * it, int pos){
    if(it->arr_len < pos){
        puts("index out of bounds");
        exit(EXIT_FAILURE);
    }
    it->position = pos;
}

Token start_iterator(TokenIterator * it){
    if(it->arr_len < 0){
        puts("no values in iterator");
        exit(EXIT_FAILURE);
    }
    it->position = 0;
    return it->arr[0];
}
