#ifndef INLINEF_H
#define INLINEF_H
#include <string.h>
#include "parseh.h"
#include "strh.h"



int is_variable_redefining(){
    FILE *file = fopen(DEFINED_IDENTIFIER_FILE_NAME, "r");
    char name[NAME_STRLEN];
    while(fgets(name, NAME_STRLEN, file)){
        trim_newline(name);
        if(strcmp(name, working_identifier) == 0){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

static inline int method_inline_function(int mln){
    if(working_identifier[0] != '\0'){
        if(is_variable_redefining()){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "Redefinition of %s", working_identifier);
            push_error(temp);
            return 1;
        }
        if( !get_function_name_from_method(mln) ){
            return 0;
        }
        if(strcmp(get_function_name_from_method(mln), "DECLARE(ID)") == 0){
            fputs_with_newl(DEFINED_IDENTIFIER_FILE_NAME, working_identifier);
        }else if(strcmp(get_function_name_from_method(mln), "DECLARE(FUNC)") == 0){
            // put function name in syntax.txt
        }
    }
    return 0;
}

#endif