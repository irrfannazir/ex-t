#include <stdio.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/strh.h"
#include "common/table.h"


static inline int is_variable_redefining(){
    return vscan(DEFINED_IDENTIFIER_FILE_NAME, working_identifier) != -1;
}

int method_inline_function(int mln){
    if(working_identifier[0] != '\0'){
        const char *fn_name = get_function_name_from_method(mln);
        const int isdeclare = fn_name && (strcmp(get_function_name_from_method(mln), "DECLARE(ID)") == 0);
        if(is_variable_redefining() && isdeclare){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "Redefinition of %s", working_identifier);
            push_error(temp);
            return 1;
        }
        if(!is_variable_redefining() && !isdeclare){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "The variable %s is not declared", working_identifier);
            push_error(temp);
            return 1;
        }
        if( !get_function_name_from_method(mln) ){
            return 0;
        }
        if(strcmp(get_function_name_from_method(mln), "DECLARE(ID)") == 0 && vscan(DEFINED_IDENTIFIER_FILE_NAME, working_identifier) == -1){
            vadd(DEFINED_IDENTIFIER_FILE_NAME, working_identifier);
        }
        if(strcmp(get_function_name_from_method(mln), "DECLARE(FUNC)") == 0){
            // put function name in syntax.txt
        }
    }
    return 0;
}