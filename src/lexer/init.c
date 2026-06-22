#include <stdio.h>
#include <string.h>
#include "lex/lexh.h"
#include "common/pc_error.h"
#include "common/fileh.h"
#include "parse/syntax.h"
#include "parse/comment.h"
#include "parse/strh.h"
#include "data.h"

#define DEFAULT_TEXT "single\narray\n"

int token_to_type(char *syn);
int does_tree_needed(char *word);

static inline void save_it_in_filename(char *str){
    FILE *fh = fopen(PARSE_KEYWORD_LIST_FILE_NAME, "a");
    if( !fh ){
        __pc_error__("Error while initiating datatype list file named %s", PARSE_KEYWORD_LIST_FILE_NAME);
        return;
    }
    fprintf(fh, "%s\n", str);
    fclose(fh);
}

static inline int check_for_keyword(char *str){
    FILE *fh = fopen(PARSE_KEYWORD_LIST_FILE_NAME, "r");
    if( !fh ){
        __pc_error__("Error while initiating datatype list file named %s", PARSE_KEYWORD_LIST_FILE_NAME);
        return -1;
    }
    char line[KEYWORD_MAX];
    while(fgets(line, KEYWORD_MAX, fh)){
        trim_newline(line);
        if(strcmp(line, str) == 0) {
            fclose(fh);
            return 1;
        }
    }
    fclose(fh);
    return 0;
}

static inline void scrap_the_keyword_from_line(char *line){
    char *token = strtok(line, " \t\n");
    while (token) {
        if(is_inline_comment(token) || is_inline_function(token)) return;
    
        if (
            is_char(token[0])          &&       //if the token starts with character
            token_to_type(token) == -1 &&       //if the token doesn't denotes any type 
            !does_tree_needed(token)   &&       //if the token doesn't generate a tree
            !check_for_keyword(token)           //if the token already saved
        ) {
            save_it_in_filename(token);
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