#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse/parseh.h"
#include "parse/perror.h"
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

int skip_to_next_line(int *mln, int *mtn){
    char *error_message = get_error_message_from_method(*mln);
    if(error_message != NULL){
        push_error(error_message);
    }
    free(error_message);
    method_inline_function(*mln);
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