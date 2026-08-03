#include "compile/sh.h"


void function_declaration(const char *dfn, int i_name){
    char temp[C_PROGRAM_MAX] = "";
    const char *name = get_token(i_name);
    snprintf(temp, sizeof(temp), "int %s(){%s}", name, PGM_CURSOR);
    insert_before_target(dfn, temp, FUNCTION_CURSOR);
}

void function_declaration_with_args(const char *dfn, int *arr, int count){
    if(count != 3) return;
    char temp[C_PROGRAM_MAX] = "";
    const char *name = get_token(arr[1]);
    snprintf(temp, sizeof(temp), "int %s(%s){%s}", name, serialize(arr[2], arr[3]), PGM_CURSOR);
    insert_before_target(dfn, temp, FUNCTION_CURSOR);
}