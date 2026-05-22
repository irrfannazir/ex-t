#include <stdio.h>
#include <string.h>
#include "data.h"




int flushf(){ 
    #ifdef DELETE_UNWANTED_FILES
    for(int i = 0; i < sizeof(unwanted_filenames)/sizeof(unwanted_filenames[0]); i++){
        if(remove(unwanted_filenames[i]) != 0 && strcmp(unwanted_filenames[i], "program.c") != 0){
            printf("%s: ", unwanted_filenames[i]);
            perror("Error on real-time data alteration");
        }
    }
    #endif
    return 0;
}