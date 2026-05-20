#ifndef PERROR_H
#define PERROR_H
#include "pdebug.h"

int append_error_message(const char *msg);
int num_lines(int size);

static inline void log_debug(const char *format, ...)
{
    #ifdef P_PARSE_DEBUG_MODE
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    #endif
}

#endif