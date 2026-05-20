#ifndef LERROR_H
#define LERROR_H
#include <stdio.h>

static inline void charerror(const char c){
    printf("Error: The unknown character '%c' is found.\n", c);
}

static inline void lexerror(const char *msg){
    printf("Error: %s\n", msg);
}

#endif