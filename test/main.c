#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minunit.h"

static char * test_parsing_tokens(){
    mu_assert("error, wrong tokens", 1 == 2);
}

int main(){
    EXIT_SUCCESS;
}
