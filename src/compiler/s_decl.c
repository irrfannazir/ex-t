#define DECLARATION
#include "compile/sh.h"


void declaration_exec(const char *fn, int *arr, int count){
    const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
    const char *id = get_token(arr[ORDER_ID]);
    static char temp[C_PROGRAM_MAX] = "";
        if(count == 3){
        sprintf(
            temp, 
            "%s %s;",
            datatype,
            id
        );
    }else if (count > 3){
        sprintf(
            temp, 
            "%s %s = %s;",
            datatype,
            id, 
            serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END])
        );
    }
    insert_before_target(fn, temp, PGM_CURSOR);
}