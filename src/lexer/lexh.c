#include <stdio.h>
#include <string.h>
#include "data.h"

int iskeyword(const char *str){
    FILE *fh = fopen(PARSE_KEYWORD_LIST_FILE_NAME, "r");
    char keyword[KEYWORD_MAX];
    while(fgets(keyword, KEYWORD_MAX, fh)){
        if (strcmp(keyword, str) == 0){
            fclose(fh);
            return 1;
        }
    }
    fclose(fh);
    return 0;
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