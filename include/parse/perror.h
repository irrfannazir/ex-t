#ifndef PERROR_H
#define PERROR_H
#include "pdebug.h"
#include <stdarg.h>

int num_lines(int size);

#ifdef P_PARSE_DEBUG_MODE
    static inline void log_debug(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
#else
    #define log_debug(...) 
#endif

#endif