#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../src/lexer.h"
#include "../src/interpreter.h"

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
        printf("%s\n", err_msg);
        return 1;
    }
    return 0;
}

int read_tokens_reads_tokens(){
    int result = 0;
    enum Token * tokens = malloc(1 * sizeof(enum Token));
    read_tokens("+", 1, tokens);
    result = assert_test("tokens dont match", tokens[0] == INC);
    read_tokens("-", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == DEC);
    read_tokens("<", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == PREV);
    read_tokens(">", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == NEXT);
    read_tokens(".", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == PRINT);
    read_tokens("[", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == LOOP_START);
    read_tokens("]", 1, tokens);
    result += assert_test("tokens dont match", tokens[0] == LOOP_END);
    free(tokens);

    return result;
}

int read_many_tokens() {
    enum Token * tokens = malloc(20 * sizeof(enum Token));
    read_tokens("+++++[>+++++++<-].", 18, tokens);
    enum Token expected[18] = {INC, INC, INC, INC, INC, LOOP_START, NEXT, INC, INC, INC, INC, INC, INC, INC, PREV, DEC, LOOP_END, PRINT};
    for(int i = 0; i < 18; i++){
        if(assert_test("token does not match", expected[i] == tokens[i]) != 0) return 1;
    }
    return 0;
}

int finds_matching_close(){
    int result = 0;
    enum Token arr[] = {LOOP_START, INC, INC, INC, LOOP_END};
    int index = findMatchingClose(0, arr, 5);
    result += assert_test("command index incorrect", index == 4);

    enum Token arr2[] = {INC, INC, INC, INC ,LOOP_START, NEXT, INC, INC, INC, PREV, DEC, LOOP_END, PRINT};
    index = findMatchingClose(4, arr2, 13);
    result += assert_test("command index incorrect", index == 11);
    return result;
}

int finds_matching_open(){
    int result = 0;
    enum Token arr[] = {LOOP_START, INC, INC, INC, LOOP_END};
    int index = findMatchingOpen(4, arr, 5);
    result += assert_test("command index incorrect", index == 0);

    enum Token arr2[] = {INC, INC, INC, INC ,LOOP_START, NEXT, INC, INC, INC, PREV, DEC, LOOP_END, PRINT};
    index = findMatchingOpen(11, arr2, 13);
    result += assert_test("command index incorrect", index == 4);
    return result;
}

int run_tests(){
    int val = 0;
    val += read_tokens_reads_tokens();
    val += finds_matching_close();
    val += finds_matching_open();
    val += read_many_tokens();
    return val;
}


int main(){
    if(run_tests() == 0){
      printf("all tests successful");
      return EXIT_SUCCESS;
    }
    printf("some tests failed");
    return EXIT_FAILURE;
}
