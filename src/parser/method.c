#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/strh.h"
#include "common/table.h"


static inline int is_variable_redefining(){
    return vscan(DEFINED_IDENTIFIER_FILE_NAME, working_identifier) != -1;
}

int method_inline_function(int mln){
    if(working_identifier[0] != '\0'){
        char *fn_name = get_function_name_from_method(mln);
        const int isdeclare = fn_name && (strcmp(fn_name, "DECLARE(ID)") == 0);
        if(is_variable_redefining() && isdeclare){
            char temp[1024 + NAME_STRLEN];
            snprintf(temp, sizeof(temp), "Redefinition of %s", working_identifier);
            push_error(temp);
            free(fn_name);
            return 1;
        }
        if(!is_variable_redefining() && !isdeclare){
            char temp[1024 + NAME_STRLEN];
            snprintf(temp, sizeof(temp), "The variable %s is not declared", working_identifier);
            push_error(temp);
            free(fn_name);
            return 1;
        }
        if( !fn_name ){
            return 0;
        }
        if(strcmp(fn_name, "DECLARE(ID)") == 0 && vscan(DEFINED_IDENTIFIER_FILE_NAME, working_identifier) == -1){
            vadd(DEFINED_IDENTIFIER_FILE_NAME, working_identifier);
        }
        if(strcmp(fn_name, "DECLARE(FUNC)") == 0){
            // put function name in syntax.txt
        }
        free(fn_name);
    }
    return 0;
}
