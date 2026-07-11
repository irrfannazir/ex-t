#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

const char *find_datatype(int index){
    char *token = get_token(index);
    if(token && strcmp(token, "single") == 0){
        free(token);
        return "int";
    }
    free(token);
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
            snprintf(descr, PSUEDO_CODE_MAX, "%s", &name[space_found + 1]);
            descr[strcspn(descr, "\n")] = '\0';
        }else{
            descr[0] = '\0';
        }
        name[space_found] = '\0';
        if (strcmp(name, datatype) == 0){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
