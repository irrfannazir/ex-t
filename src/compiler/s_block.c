#define BLOCK_PARADIGMA
#include "compile/sh.h"


void else_condition(int *arr, int count){
    static char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "else{%s}", PGM_CURSOR);
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}

void block_paradigm(char *keyword, int *arr, int count){
    const char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
    static char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "%s(%s){%s}", keyword, expression, PGM_CURSOR);
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}


