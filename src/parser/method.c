#include <stdio.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/strh.h"


static inline int is_variable_redefining(){
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

int method_inline_function(int mln){
    if(working_identifier[0] != '\0'){
        if(is_variable_redefining() && strcmp(get_function_name_from_method(mln), "DECLARE(ID)") == 0){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "Redefinition of %s", working_identifier);
            push_error(temp);
            return 1;
        }
        if(!is_variable_redefining() &&
            ( get_function_name_from_method(mln) == NULL || strcmp(get_function_name_from_method(mln), "DECLARE(ID)") != 0)
        ){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "The variable %s is not declared", working_identifier);
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