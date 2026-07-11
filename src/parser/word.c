#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/comment.h"
#include "parse/syntax.h"
#include "common/pc_error.h"

#define MAX_LINE_LENGTH 1024

char *get_word_from_method(int line_number, int token_number) {
    FILE *file = fopen(METHOD_DIRECTORY, "r");
    if (!file) {
        __pc_error__("Error while retrieving method word from the file named %s", METHOD_DIRECTORY);
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int current_line = 0;

    
    while (fgets(line, sizeof(line), file)) {
        if(is_inline_comment(line)){
            continue;
        }
        if (current_line == line_number) {
            fclose(file);

            
            char *token = strtok(line, " \n");
            int current_token = 0;

            while (token) {
                if (current_token == token_number) {
                    
                    char *result = malloc(strlen(token) + 1);
                    if (result) {
                        memcpy(result, token, strlen(token) + 1);
                        if ( is_inline_comment(result) || is_inline_function(result) ){
                            free(result);
                            return NULL;
                        }
                        return result;
                    } else {
                        return NULL; 
                    }
                }
                token = strtok(NULL, " \n");
                current_token++;
            }

            return NULL; 
        }
        current_line++;
    }

    fclose(file);
    return NULL; 
}


