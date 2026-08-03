#define PRINT_STATEMENT
#include <stdlib.h>
#include "compile/sh.h"

typedef enum {
    NO,
    TI,
    TO
}p_prev;

static int append_text(char *dest, size_t dest_size, const char *src){
    if (!src) return 1;
    size_t used = strlen(dest);
    size_t available = dest_size - used;
    int written = snprintf(dest + used, available, "%s", src);
    return written < 0 || (size_t)written >= available;
}

void print_statement(const char *ffn, const char *efn, int *arr, int count){
    char format[C_PROGRAM_MAX] = "";
    char para[C_PROGRAM_MAX] = "";
    char temp[C_PROGRAM_MAX] = "";
    p_prev flag = NO;
    add_the_header(ffn, "stdio.h");
    // insert_newline_before_target(fn, INCLUDE_CURSOR);
    for(int i = arr[ORDER_PRINT_START]; i < arr[ORDER_PRINT_END]; i++){
        char *token = get_token(i);
        if (!token) continue;
        if(strcmp(token, ",") == 0){
            flag = NO;
        }else if(get_type(i) == TOKEN_STRING){
            if (append_text(format, sizeof(format), token)) {
                free(token);
                return;
            }
        }else if(get_type(i) == TOKEN_IDENTIFIER || get_type(i) == TOKEN_INTEGER){
            if( strcmp(para, "") == 0 && append_text(para, sizeof(para), ",")) {
                free(token);
                return;
            }
            switch(flag){
                case NO:
                    if (append_text(format, sizeof(format), "%d") ||
                        (strcmp(para, ",") != 0 && append_text(para, sizeof(para), ", ")) ||
                        append_text(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                case TI:
                    if (append_text(format, sizeof(format), "%d") ||
                        append_text(para, sizeof(para), ", ") ||
                        append_text(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                case TO:
                    if (append_text(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
            }
            flag = TI;
        }else if(get_type(i) == TOKEN_OPERATOR){
            switch(flag){
                case TI:
                    if (append_text(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                case NO:
                case TO:
                    break;
            }
            flag = TO;
        }
        free(token);
    }
    if (snprintf(temp, sizeof(temp), "printf(\"%s\"%s);", format, para) >= (int)sizeof(temp)) {
        return;
    }
    insert_before_target(efn, temp, PGM_CURSOR);
    fputs_with_newl(PARSED_INFORMATION, "Implement");
}
