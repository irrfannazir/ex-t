#include <stdio.h>
#include <string.h>
#include "data.h"
#include "common/table.h"

int iskeyword(const char *str){
    return vscan(PARSE_KEYWORD_LIST_FILE_NAME, str) != -1;
}

int isdatatype(const char *str){
    FILE *fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    
    char name[256];
    
    while (fgets(name, sizeof(name), fp)) {
        name[strcspn(name, "\n")] = '\0';    
        if (strcmp(name, str) == 0)
            return 1;
    }

    fclose(fp);
    return 0;
}