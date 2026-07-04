#define PRINT_STATEMENT
#include <stdlib.h>
#include "compile/sh.h"

typedef enum {
    NO,
    TI,
    TO
}p_prev;

void print_statement(const char *ffn, const char *efn, int *arr, int count){
    char format[C_PROGRAM_MAX] = "";
    char para[C_PROGRAM_MAX] = "";
    char temp[C_PROGRAM_MAX*100] = "";
    p_prev flag = NO;
    add_the_header(ffn, "stdio.h");
    // insert_newline_before_target(fn, INCLUDE_CURSOR);
    for(int i = arr[ORDER_PRINT_START]; i < arr[ORDER_PRINT_END]; i++){
        char *token = get_token(i);
        if(strcmp(token, ",") == 0){
            flag = NO;
        }else if(get_type(i) == TOKEN_STRING){
            strcat(format, token);
        }else if(get_type(i) == TOKEN_IDENTIFIER || get_type(i) == TOKEN_INTEGER){
            if( strcmp(para, "") == 0 ) strcat(para, ",");
            switch(flag){
                case NO:
                    strcat(format, "%d");
                    strcat(para, token);
                    break;
                case TI:
                    strcat(format, "%d");
                    strcat(para, ", ");
                    strcat(para, token);
                    break;
                case TO:
                    strcat(para, token);
                    break;
            }
            flag = TI;
        }else if(get_type(i) == TOKEN_OPERATOR){
            switch(flag){
                case TI:
                    strcat(para, token);
                    break;
            }
            flag = TO;
        }
        free(token);
    }
    sprintf(temp, "printf(\"%s\"%s);", format, para);
    insert_before_target(efn, temp, PGM_CURSOR);
    sprintf(temp, "Implement %s as per the function in c", temp);
    fputs_with_newl(PARSED_INFORMATION, "Implement");
}