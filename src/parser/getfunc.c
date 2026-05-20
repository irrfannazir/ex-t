#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/syntax.h"
#include "parse/comment.h"
#include "common/pc_error.h"

#define MAX_LINE_LEN 1024

char *get_function_name_from_method(int line_number) {
    FILE *file = fopen(METHOD_DIRECTORY, "r");
    if (!file) {
        __pc_error__("Error while retrieving error message from file %s", METHOD_DIRECTORY);
        return NULL;
    }

    char line[MAX_LINE_LEN];
    int current_line = 0;

    while (fgets(line, sizeof(line), file)) {
        if(is_inline_comment(line)) continue;
        
        if (current_line == line_number) {
            fclose(file);

            // Look for '$$'
            char *comment_start = strstr(line, SYNTAX_FUNCTION_TOKEN);
            if (!comment_start) return NULL;

            comment_start += 2;

            // Skip whitespace
            while (*comment_start == ' ' || *comment_start == '\t') comment_start++;

            // Remove trailing newline
            char *newline = strchr(comment_start, '\n');
            if (newline) *newline = '\0';

            // Allocation
            char *result = malloc(strlen(comment_start) + 1);
            if (!result) return NULL;

            strcpy(result, comment_start);
            return result;
        }

        current_line++;
    }

    fclose(file);
    return NULL;  // Line not found
}