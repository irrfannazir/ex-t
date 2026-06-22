#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse/perror.h"
#include "parse/parseh.h"
#include "parse/comment.h"
#include "parse/syntax.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "common/table.h"
#include "data.h"

static inline int is_variable_declared(int index){
    return vscan(DEFINED_IDENTIFIER_FILE_NAME, working_identifier) != -1;
}

void handle_identifier_declaration(int index, int method_line_num) {
    const char *syntax = read_nth_content_werror(METHOD_DIRECTORY, method_line_num);
    if (syntax && get_type(index) == TOKEN_IDENTIFIER && strstr(syntax, SYNTAX_FUNCTION_TOKEN) != NULL){
        strcpy(working_identifier, get_token(index));
    }
}

void handle_undeclared_variable(int index, int method_line_num){
    const char *syntax = read_nth_content_werror(METHOD_DIRECTORY, method_line_num);
    if(
        get_type(index) == TOKEN_IDENTIFIER &&
        !is_variable_declared(index)
    ){
        strcpy(working_identifier, get_token(index));
    }
}

void clear_identifier_buffer(){
    working_identifier[0] = '\0';
}

static inline int check_the_type(char *word, t_type type){
    const int temp = token_to_type(word);
    if(temp == -1) return 0;
    return (temp == (int) type);
}

int try_match_type(char *word, int index, int *method_token_num) {
    if (check_the_type(word, get_type(index))) {
        log_debug("\tSimiliar type found\n");
        push_to_parse_string(index);
        next_token(method_token_num);
        return 1;
    }
    return 0;
}

int try_match_word(char *word, int index, int *method_token_num) {
    if (compare_the_word(word, get_token(index))) {
        log_debug("\tSimiliar word found\n");
        next_token(method_token_num);
        return 1;
    }
    return 0;
}

// Returns 1 if the tree was processed and the loop should continue,
// returns 0 if the caller should skip to next method.
int handle_syntax_tree(char *word, int index,
                              int *method_line_num, int *method_token_num) {
    int start = lsn + ltn - 1;   // global line+token offset
    int size;
    next_token(method_token_num);
    char *end = get_word_from_method(*method_line_num, *method_token_num);
    log_debug("\tA syntax tree found.\n");

    if (!end) {
        // No ending keyword: consume all remaining tokens
        int prev;
        while (index != -1) {
            prev = index;
            index = get_index_from_lex(1);
        }
        size = prev - start + 1;
    } else {
        // Search for the ending keyword
        while (index != -1) {
            index = get_index_from_lex(1);
            if(get_token(index) == NULL){
                pushError(ERROR_HANDLING_FILENAME, *method_line_num, "Doesn't found an keyword named %s\n", end);
                dont_compile = 1;
                return 0;
            }
            
            if (compare_the_word(end, get_token(index))) {
                break;
            }
        }
        if (index == -1) {
            pushError(ERROR_HANDLING_FILENAME, *method_line_num, "Expected an operator %s\n", end);
            skip_to_next_method(method_line_num, method_token_num);
            return 1;   // error handled, continue outer loop
        }
        (*method_token_num)++;
        size = index - start;
    }

    push_to_parse_string(start);
    push_to_parse_string(start + size);
    int status = parsing_tree_analysis(word, start, size);
    if (status) {
        print_error();
        skip_to_next_line(method_line_num, method_token_num);
    }
    if (end == NULL) {
        skip_to_next_line(method_line_num, method_token_num);
    }
    return 1;   // tree processed, continue loop
}