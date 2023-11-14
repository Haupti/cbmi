#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../src/lexer.h"

int assert_str(char * expected, char * actual){
    if(strcmp(expected, actual) != 0) {
        printf("Strings not equal: expected \"%s\" but got \"%s\"", expected, actual);
        return 1;
    }
    return 0;
}
int assert_int(int expected, int actual){
    if(expected != actual) {
        printf("Ints not equal: expected \"%d\" but got \"%d\"", expected, actual);
        return 1;
    }
    return 0;
}

int assert_test(char * err_msg, int test){
    if(test != 1){
        printf("%s", err_msg);
        return 1;
    }
    return 0;
}

int read_tokens_reads_tokens(){
    int result = 0;
    char * program = "+";
    enum Token * tokens = malloc(1 * sizeof(enum Token));
    read_tokens(program, 1, tokens);
    result = assert_test("tokens dont match", tokens[0] == INC);
    printf("%d", tokens[0]);
    free(tokens);

    return result;
}

int run_tests(){
    int val = 0;
    val += read_tokens_reads_tokens();
    return val;
}


int main(){
    if(run_tests() == 0){
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
