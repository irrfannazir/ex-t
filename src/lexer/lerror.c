#include <stdio.h>

void charerror(const char c){
    printf("Error: The unknown character '%c' is found.\n", c);
}

void lexerror(const char *msg){
    printf("Error: %s\n", msg);
}