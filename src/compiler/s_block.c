#define BLOCK_PARADIGMA
#include "compile/sh.h"


void else_condition(const char *fn){
    char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "else{%s}", PGM_CURSOR);
    insert_before_target(fn, temp, PGM_CURSOR);
}

void block_paradigm(const char *fn, char *keyword, int *arr, int count){
    if (count != 3) return;
    const char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
    char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "%s(%s){%s}", keyword, expression, PGM_CURSOR);
    insert_before_target(fn, temp, PGM_CURSOR);
}


