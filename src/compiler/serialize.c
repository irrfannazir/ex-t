#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


char *serialize(int start, int end) {
    size_t buffer_size = 1024; 
    char *result = malloc(buffer_size);
    if (!result) return NULL;
    result[0] = '\0';
    size_t length = 0;
    
    for (int i = start; i < end; ++i) {
        char *token = get_token(i);
        if (!token) continue;

        size_t token_len = strlen(token);
        size_t separator_len = (i < end - 1) ? 1 : 0;
        size_t needed_size = length + token_len + separator_len + 1; 
        if (needed_size > buffer_size) {
            while (needed_size > buffer_size) {
                buffer_size *= 2;
            }
            char *resized = realloc(result, buffer_size);
            if (!resized) {
                free(token);
                free(result);
                return NULL;
            }
            result = resized;
        }

        memcpy(result + length, token, token_len);
        length += token_len;
        if (i < end - 1) {
            result[length++] = ' ';
        }
        result[length] = '\0';
        free(token);
    }

    return result;
}
