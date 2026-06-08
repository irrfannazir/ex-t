#ifndef PC_ERROR_H
#define PC_ERROR_H
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>


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


#define FLAG_SIZE 1
#define FLAGS_TO_INT(TYPE, ...) \
    ({ \
        uint8_t __flags[] = { __VA_ARGS__ }; \
        TYPE __result = 0; \
        for (int __i = 0; __i < sizeof(__flags)/sizeof(__flags[0]); __i++) { \
            __result <<= FLAG_SIZE;\
            __result |= __flags[__i]; \
        } \
        __result; \
    })
;

#endif