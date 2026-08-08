#include <stdio.h>
#include <string.h>
#include "data.h"
#include "common/fileh.h"




int flushf(){ 
    #ifdef DELETE_UNWANTED_FILES
    for(int i = 0; i < sizeof(unwanted_filenames)/sizeof(unwanted_filenames[0]); i++){
        if(remove(unwanted_filenames[i]) != 0 && strcmp(unwanted_filenames[i], "program.c") != 0){
            printf("%s: ", unwanted_filenames[i]);
            perror("Error on real-time data alteration");
        }
    }
    #endif
    int i = 0;
    char fn[sizeof(SYMTAB_FILE_NAME_FORMAT)];
    SYMTAB_FILE_NAME(fn, i);
    while(file_exists(fn)){
        delete_file(fn);
        i++;
        SYMTAB_FILE_NAME(fn, i);
    }
    return 0;
}