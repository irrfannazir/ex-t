#include <stdio.h>
#include "common/pc_error.h"

int clear_file(const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file){
        __pc_error__("Error while clearing file named %s", filename);
        fclose(file);
        return 1;
    }

    
    fclose(file);
    return 0;
}


int delete_file(const char *filename){
    if(remove(filename) != 0){
        perror("Error on real-time data alteration");
        return 1;
    }
    return 0;
}

