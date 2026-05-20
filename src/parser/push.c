#include <stdio.h>
#include <string.h>
#include "parse/parseh.h"
#include "common/pc_error.h"
#include "data.h"

char parsed_token[PARSE_DETAILS_MAX];

int append_token_details(int mln){
    if(strcmp(parsed_token, "") == 0){
        return 0;
    }
    FILE *file = fopen(PARSING_HANDLING_FILE_NAME, "a");
    if( !file ){
        __pc_error__("Error while appending the parsed data to file named %s", PARSING_HANDLING_FILE_NAME);
        return 1;
    }
    fprintf(file, "%d %s\n", mln, parsed_token);
    fclose(file);
    strcpy(parsed_token, "");
    return 0;
}

void push_to_parse_string(int index){
    char temp[DIGIT];
    itoaf(index, temp, 10);
    strcat(parsed_token, temp);
    strcat(parsed_token, " ");
}
