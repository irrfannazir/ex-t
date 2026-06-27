#define ASSIGNMENT
#include <stdio.h>
#include "compile/sh.h"

void assign_exec(const char *dfn, int *arr, int count){
    if(count != 4) return;
    const char *id = get_token(arr[ORDER_ID]);
    char temp[C_PROGRAM_MAX] = "";
    sprintf(
        temp, 
        "%s = %s;",
        id,
        serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END])
    );
    insert_before_target(dfn, temp, PGM_CURSOR);
}