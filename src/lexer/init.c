#include <stdio.h>
#include <string.h>
#include "lex/lexh.h"
#include "common/pc_error.h"
#include "common/fileh.h"
#include "common/table.h"
#include "parse/syntax.h"
#include "parse/comment.h"
#include "parse/strh.h"
#include "data.h"

#define DEFAULT_TEXT "single allocates memory of 4 bytes and saves as signed integer format\n" \
        "array allocates memory of 4 and saves the address.\n"

int token_to_type(char *syn);
int does_tree_needed(char *word);

static inline void scrap_the_keyword_from_line(char *line){
    char *token = strtok(line, " \t\n");
    while (token) {
        if(is_inline_comment(token) || is_inline_function(token)) return;
    
        if (
            is_char(token[0])          &&                       //if the token starts with character
            token_to_type(token) == -1 &&                       //if the token doesn't denotes any type 
            !does_tree_needed(token)   &&                       //if the token doesn't generate a tree
            vscan(PARSE_KEYWORD_LIST_FILE_NAME, token) == -1    //if the token is not already saved
        ) {
            vadd(PARSE_KEYWORD_LIST_FILE_NAME, token);
        }
    
        token = strtok(NULL, " \t\n");
    }
}

static inline void init_keywords(){

    FILE *input = fopen(METHOD_DIRECTORY, "r");
    if (!input) {
        perror("Failed to open input file");
        return;
    }
    
    char line[METHOD_LINE_MAX];
    while (fgets(line, METHOD_LINE_MAX, input)) {
        if(is_inline_comment(line)) continue;
        scrap_the_keyword_from_line(line);
    }
    
    fclose(input);
}

void init_stat() {
    create_file(PARSE_DATATYPE_LIST_FILE_NAME, DEFAULT_TEXT);
    create_file(PARSE_KEYWORD_LIST_FILE_NAME, "");
    init_keywords();
}