#include <stdlib.h>
#include <stdio.h>
#include "data.h"

void compile_file(const char *filename){
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -o out", filename);
    int result = system(compile_command);

    if (result == 0) {
        printf("Compilation successful. Executable created as 'out'.\n");
    } else {
        printf("Compilation failed.\n");
    }
}


