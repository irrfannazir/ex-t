#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/syntax.h"
#include "parse/comment.h"
#include "parse/perror.h"
#include "common/pc_error.h"
#include "common/errorm.h"

#define MAX_LINE_LEN 1024

extern int lsn;


char *get_error_message_from_method(int line_number) {
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

            
            char *comment_start = strstr(line, SYNTAX_COMMENT_TOKEN);
            if (!comment_start) {
                return NULL;
            }

            comment_start += 2;

            
            while (*comment_start == ' ' || *comment_start == '\t') {
                comment_start++;
            }

            
            char *newline = strchr(comment_start, '\n');
            if (newline) *newline = '\0';

            
            char *result = malloc(strlen(comment_start) + 1);
            if (!result) return NULL;

            memcpy(result, comment_start, strlen(comment_start) + 1);
            return result;
        }

        current_line++;
    }

    fclose(file);
    return NULL;  
}

void report_method_error(int method_line_num) {
    char *msg = get_error_message_from_method(method_line_num);
    if (msg != NULL) {
        printf("Error (%d): %s\n", num_lines(lsn), msg);
    } else {
        printf("Error (%d): %s\n", num_lines(lsn), "Invalid Syntax");
    }
    free(msg);
}
