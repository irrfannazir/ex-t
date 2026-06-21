#include <string.h>
#include "lex/dfah.h"


int token_to_type(char *syn){
    if(strcmp(syn, "TOKEN_DATATYPE") == 0)  return (int) TOKEN_DATATYPE;
    if(strcmp(syn, "TOKEN_ID") == 0)        return (int) TOKEN_IDENTIFIER;
    if(strcmp(syn, "TOKEN_INTEGER") == 0)   return (int) TOKEN_INTEGER;
    if(strcmp(syn, "TOKEN_STRING") == 0)    return (int) TOKEN_STRING;
    return -1;
}
