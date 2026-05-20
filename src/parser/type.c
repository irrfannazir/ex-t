#include <string.h>
#include "lex/dfah.h"


int token_to_type(char *syn){
    if(strcmp(syn, "TOKEN_DATATYPE") == 0){
        return (int) TOKEN_DATATYPE;
    }else if(strcmp(syn, "TOKEN_ID") == 0){
        return (int) TOKEN_IDENTIFIER;
    }else if(strcmp(syn, "TOKEN_INTEGER") == 0){
        return (int) TOKEN_INTEGER;
    }
    return -1;
}

int check_the_type(char *word, t_type type){
    int temp = token_to_type(word);
    if(temp == -1){
        return 0;
    }
    return (temp == (int) type);
}


