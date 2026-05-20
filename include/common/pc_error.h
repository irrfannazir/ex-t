#ifndef PC_ERROR_H
#define PC_ERROR_H
#include <stdio.h>
#include <stdarg.h>


#define __pc_error__(...) __pc_error_impl__(__FILE__, __LINE__, __VA_ARGS__)

#define __if_it_is_null__(STR, END, MSG, ...)   \
    if(STR == NULL){                            \
        printf(MSG, ##__VA_ARGS__);       \
        END;                                    \
    }

    
static inline void __pc_error_impl__(const char *file, int line, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    printf("%s:%d: ", file, line);
    vprintf(msg, args);
    puts("\n");
}


#endif