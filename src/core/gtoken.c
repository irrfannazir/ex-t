#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/pc_error.h"
#include "data.h"

char *get_token(int index) {
    FILE *file = fopen(LEX_HANDLING_FILE_NAME, "r");
    if ( !file ) {
        __pc_error__("Error while opening lex file named %s", LEX_HANDLING_FILE_NAME);
        return NULL;
    }

    char *str = malloc(100 * sizeof( char )); 
    char line[256];
    int num;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        str[0] = '\0';

        int fields = sscanf(line, "%d %99[^\n]", &num, str);

        if (fields >= 1 && num != -1) {
            if(count == index){
                fclose(file);
                return str;
            }
            count++;
        }
    }

    fclose(file);
    return NULL;
}