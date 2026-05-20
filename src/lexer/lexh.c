#include <stdio.h>
#include <string.h>
#include "data.h"

int iskeyword(const char *str){
    const char *keywords[] = {"if", "else", "new", "for", "while", "print"};
    for (int i = 0; i < sizeof(keywords)/ sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], str) == 0)
            return 1;
    }
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