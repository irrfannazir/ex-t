#define ASSIGNMENT
#include <stdio.h>
#include <stdlib.h>
#include "compile/sh.h"

void assign_exec(const char *dfn, int *arr, int count){
    if(count != 4) return;
    char *id = get_token(arr[ORDER_ID]);
    char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
    if (!id || !expression) {
        free(id);
        free(expression);
        return;
    }
    char temp[C_PROGRAM_MAX] = "";
    if (snprintf(
        temp, 
        sizeof(temp),
        "%s = %s;",
        id,
        expression
    ) >= (int)sizeof(temp)) {
        free(id);
        free(expression);
        return;
    }
    char psuedo[PSUEDO_CODE_MAX] = "";
    if (snprintf(
        psuedo,
        sizeof(psuedo),
        "Assign the value (%s) to variable %s",
        expression,
        id
    ) >= (int)sizeof(psuedo)) {
        free(id);
        free(expression);
        return;
    }
    insert_before_target(dfn, temp, PGM_CURSOR);
    fputs_with_newl(PARSED_INFORMATION, psuedo);
    free(id);
    free(expression);
}
