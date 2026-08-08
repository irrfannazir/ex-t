#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/strh.h"
#include "common/table.h"

extern int block_depth;

static inline int is_variable_redefining(){
    char fn[sizeof(SYMTAB_FILE_NAME_FORMAT)];
    for(int i = 0 ; i <= block_depth; i++){
        SYMTAB_FILE_NAME(fn, i);
        return vscan(fn, working_identifier) != -1;
    }
    SYMTAB_FILE_NAME(fn, block_depth);
    return 0;
}

int method_inline_function(int mln){
    if(working_identifier[0] != '\0'){
        char *fn_name = get_function_name_from_method(mln);
        const int isdeclare = fn_name && (strcmp(fn_name, "DECLARE(ID)") == 0);
        int variable_declared = is_variable_redefining();
        if(variable_declared && isdeclare){
            char temp[1024 + NAME_STRLEN];
            snprintf(temp, sizeof(temp), "Redefinition of %s", working_identifier);
            push_error(temp);
            free(fn_name);
            return 1;
        }
        if(!variable_declared && !isdeclare){
            char temp[1024 + NAME_STRLEN];
            snprintf(temp, sizeof(temp), "The variable %s is not declared", working_identifier);
            push_error(temp);
            free(fn_name);
            return 1;
        }
        if( !fn_name ){
            return 0;
        }
        char fn[sizeof(SYMTAB_FILE_NAME_FORMAT)];
        SYMTAB_FILE_NAME(fn, block_depth);
        if(strcmp(fn_name, "DECLARE(ID)") == 0 && !variable_declared){
            vadd(fn, working_identifier);
        }
        if(strcmp(fn_name, "DECLARE(FUNC)") == 0){
            // put function name in syntax.txt
        }
        free(fn_name);
    }
    return 0;
}
