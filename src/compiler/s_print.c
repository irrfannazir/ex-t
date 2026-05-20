#include "compile/sh.h"

typedef enum {
    NO,
    TI,
    TO
}p_prev;

void print_statement(int *arr, int count){
    static char format[C_PROGRAM_MAX] = "";
    static char para[C_PROGRAM_MAX] = "";
    static char temp[C_PROGRAM_MAX*100] = "";
    p_prev flag = NO;
    add_the_header(PGM_EXATED_FILE_NAME, "stdio.h");
    // insert_newline_before_target(PGM_EXATED_FILE_NAME, INCLUDE_CURSOR);
    for(int i = arr[1]; i < arr[2]; i++){
        if(strcmp(get_token(i), ",") == 0){
            flag = NO;
        }else if(get_type(i) == TOKEN_STRING){
            strcat(format, get_token(i));
        }else if(get_type(i) == TOKEN_IDENTIFIER || get_type(i) == TOKEN_INTEGER){
            if( strcmp(para, "") == 0 ) strcat(para, ",");
            switch(flag){
                case NO:
                    strcat(format, "%d");
                    strcat(para, get_token(i));
                    break;
                case TI:
                    strcat(format, "%d");
                    strcat(para, ", ");
                    strcat(para, get_token(i));
                    break;
                case TO:
                    strcat(para, get_token(i));
                    break;
            }
            flag = TI;
        }else if(get_type(i) == TOKEN_OPERATOR){
            switch(flag){
                case TI:
                    strcat(para, get_token(i));
                    break;
            }
            flag = TO;
        }
    }
    sprintf(temp, "printf(\"%s\"%s);", format, para);
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}