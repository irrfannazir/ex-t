#include <string.h>
#include <stdio.h>
#include "data.h"

const char *find_datatype(int index){
    if(strcmp(get_token(index), "single") == 0){
        return "int";
    }
    return NULL;
}

int get_description(const char *datatype, char *descr){
    FILE *fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    
    char name[256];
    
    while (fgets(name, sizeof(name), fp)) {
        int space_found = strcspn(name, " \n");
        if(name[space_found] == ' '){
            strcpy(descr, &name[space_found + 1]);
            descr[strcspn(descr, "\n")] = '\0';
        }else{
            descr[0] = '\0';
        }
        name[space_found] = '\0';
        if (strcmp(name, datatype) == 0)
            return 1;
    }

    fclose(fp);
    return 0;
}