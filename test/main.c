#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int run_tests(){
    int val = 0;
    val += assert_str("test", "test");
    return val;
}


int main(){
    if(run_tests() == 0){
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
