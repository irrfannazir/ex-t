#include <stdio.h>
#include <string.h>
#include "parse/nexth.h"
#include "common/pc_error.h"
#include "data.h"

char parsed_token[PARSE_DETAILS_MAX];

static int append_to_parsed_token(const char *text){
    size_t used = strlen(parsed_token);
    if (used >= sizeof(parsed_token)) return 1;
    int written = snprintf(parsed_token + used, sizeof(parsed_token) - used, "%s", text);
    return written < 0 || (size_t)written >= sizeof(parsed_token) - used;
}

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
    parsed_token[0] = '\0';
    return 0;
}

void push_to_parse_string(int index){
    char temp[DIGIT];
    itoaf(index, temp, 10);
    if (append_to_parsed_token(temp)) return;
    append_to_parsed_token(" ");
}
