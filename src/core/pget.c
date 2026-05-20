#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/pc_error.h"
#include "data.h"

#define LINE_MAX 256
#define LEXEME_MAX (LINE_MAX - 2)

int get_indentation(int index){
    FILE *file = fopen(LEX_HANDLING_FILE_NAME, "r");
    if ( !file ) {
        __pc_error__("Error while opening lex file named %s", LEX_HANDLING_FILE_NAME);
        return -1;
    }

    char line[LINE_MAX];
    char str[LEXEME_MAX];
    int num;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        str[0] = '\0';
        int fields = sscanf(line, "%d %99s", &num, str);
        if (fields == 2 && num == -1 && str[0] != '\0') {
            if(count == index){
                fclose(file);
                return atoi(str); 
            }
            count++;
        }
    }

    fclose(file);
    return -1;
}

t_type get_type(int index){
    FILE *file = fopen(LEX_HANDLING_FILE_NAME, "r");
    if ( !file ) {
        __pc_error__("Error while opening lex file named %s", LEX_HANDLING_FILE_NAME);
        return TOKEN_NULL;
    }
    
    char str[100];
    char line[256];
    int num;
    int count = 0;
    t_type type;
    
    while (fgets(line, sizeof(line), file)) {
        str[0] = '\0';
    
        int fields = sscanf(line, "%d %99[^\n]", &num, str);
    
        if (fields >= 1 && num != -1) {
            if(count == index){
                fclose(file);
                type = num;
                return type;
            }
            count++;
        }
    }
    
    fclose(file);
    return TOKEN_NULL;
}

void get_type_token(int index, t_type *type, char *str){
    FILE *file = fopen(LEX_HANDLING_FILE_NAME, "r");
    if ( !file ) {
        __pc_error__("Error while opening lex file named %s", LEX_HANDLING_FILE_NAME);
        return;
    }
    char line[256];
    int num;
    int count = 1;
    
    while (fgets(line, sizeof(line), file)) {
        str[0] = '\0';

        int fields = sscanf(line, "%d %99[^\n]", &num, str);
        
        if (fields >= 1 && num != -1) {
            if(count == index){
                fclose(file);
                *type = num;
                return;
            }
            count++;
        }
    }
    
    fclose(file);
    *type = TOKEN_NULL;
    str = NULL;
}


