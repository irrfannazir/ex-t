#define DECLARATION
#include <stdlib.h>
#include "compile/sh.h"


void declaration_exec(const char *fn, int *arr, int count){
    if(count < 3) return;
    const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
    const char *id = get_token(arr[ORDER_ID]);
    char temp[C_PROGRAM_MAX] = "";
        if(count == 3){
        sprintf(
            temp, 
            "%s %s;",
            datatype,
            id
        );
    }else if (count > 3){
        const char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
        sprintf(
            temp, 
            "%s %s = %s;",
            datatype,
            id, 
            expression
        );
        free((char *)expression);
    }
    free((char *)id);
    insert_before_target(fn, temp, PGM_CURSOR);
}