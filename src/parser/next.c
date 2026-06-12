#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse/parseh.h"
#include "parse/perror.h"
#include "parse/syntax.h"
#include "parse/comment.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "common/fileh.h"
#include "data.h"


int lsn = 0;
int ltn = 0;

int method_inline_function(int mln);

int get_index_from_lex(int cl){
    if(get_type(lsn+ltn) == TOKEN_EOF){
        return -1;
    }else{
        if(cl){
            ltn++;
        }
        return lsn+ltn-1;
    }
}

#define MAX_LINE_LENGTH 1024

static inline int count_inline_comment_until(int mln){
    FILE *file = fopen(METHOD_DIRECTORY, "r");
    if (!file) {
        __pc_error__("Error while retrieving method word from the file named %s", METHOD_DIRECTORY);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int current_line = 0;
    int inline_comment_count = 0;

    // Read lines until reaching the desired one
    while (fgets(line, sizeof(line), file)) {
        if(is_inline_comment(line)) continue;
        if(is_inline_comment(strstr(line, SYNTAX_COMMENT_TOKEN))) inline_comment_count++;        
        if (current_line == mln) return inline_comment_count;
        current_line++;
    }

    fclose(file);
    return 0; // Line not found
}

int skip_to_next_line(int *mln, int *mtn){
    char *error_message = get_error_message_from_method(*mln);
    if(error_message != NULL){
        push_error(error_message);
    }
    free(error_message);
    method_inline_function(*mln - count_inline_comment_until(*mln));
    if(error != NULL){
        printf("Error (%d): ", num_lines(lsn));
        dont_compile = 1;
    }else{
        append_token_details(*mln);
    }
    while(get_type(lsn) != TOKEN_EOF && get_type(lsn) != TOKEN_NULL){
        lsn++;
    }
    lsn++;
    ltn = 0;
    *mtn = 0;
    *mln = 0;
    print_error();
    strcpy(parsed_token, "");
    if(get_token(lsn) == NULL || get_type(lsn) != TOKEN_NULL){
        return 1;
    }
    return 0;
}

int next_token(int *mtn){
    (*mtn)++;
    error_priority++;
    return 0;
}

int skip_to_next_method(int *mln, int *mtn){
    ltn = 0;
    (*mln)++;
    *mtn = 0;
    current_error_priority = error_priority;
    strcpy(parsed_token, "");
    return 0;
}

//To count number of lines
int num_lines(int size){
    int res = 0;
    for(int i = 0;i < size; i++){
        if(get_type(i) == TOKEN_EOF){
            res++;
        }
    }
    return res;
}