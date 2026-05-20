#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


char *serialize(int start, int end) {
    size_t buffer_size = 1024; // Initial buffer size
    char *result = malloc(buffer_size);
    if (!result) return NULL;
    result[0] = '\0';
    
    for (int i = start; i < end; ++i) {
        const char *token = get_token(i);
        if (!token) continue;

        // Reallocate if necessary
        size_t needed_size = strlen(result) + strlen(token) + 2; // +1 for space, +1 for \0
        if (needed_size > buffer_size) {
            buffer_size *= 2;
            result = realloc(result, buffer_size);
            if (!result) return NULL;
        }

        strcat(result, token);
        if (i < end - 1) {
            strcat(result, " ");
        }
    }

    return result;
}
