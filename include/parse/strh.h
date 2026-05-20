#ifndef P_STRH_H
#define P_STRH_H
#include <stddef.h>
#include <string.h>

static inline size_t trim_newline(char *line) {
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
        line[--len] = '\0';
    }
    return len;
}

#endif