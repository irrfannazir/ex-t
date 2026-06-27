#define DECLARATION
#include <stdlib.h>
#include "compile/sh.h"


void declaration_exec(const char *fn, int *arr, int count){
    char temp[C_PROGRAM_MAX] = "";
    switch(count){
        case 3: //Declaration without assigning
        {
            const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
            const char *id = get_token(arr[ORDER_ID]);
            sprintf(
                temp, 
                "%s %s;",
                datatype,
                id
            );
        }
        break;
        case 5: //Declaration with assigning
        {
            const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
            const char *id = get_token(arr[ORDER_ID]);
            const char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
            sprintf(
                temp, 
                "%s %s = %s;",
                datatype,
                id, 
                expression
            );
            free((char *)expression);
            free((char *)id);
            free((char *)id);
        }
        break;
        default:
            return;
    }
    insert_before_target(fn, temp, PGM_CURSOR);
}