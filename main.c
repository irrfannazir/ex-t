#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "lex/lfh.h"
#include "lex/lfn.h"
#include "common/constants.h"
#include "data.h"

#define FINAL_COMPILED_FILENAME "finalpgm.c"


#define BUFFER_MAX 1024
#define FILE_NAME_MAX 1024

int combine_the_files(char *fn1, char * fn2);

extern int dont_compile;

int main(int argc, char *argv[]){
    char buffer[1024] = "";
    char *cache[1024];
    int size_cache = 0;
    if(argc < 3) return 1;
    for(int i = 1; i < argc; i++){
        if(new_file_name(argv[i])){ 
            char dest[FILE_NAME_MAX];
            const int isinline = get_dest_filename(dest, argv[i]);
            lexf(argv[i], LEX_HANDLING_FILE_NAME, isinline);
            parsef(PARSING_HANDLING_FILE_NAME);
            if(dont_compile) return 1;
            compilef(PARSING_HANDLING_FILE_NAME, PROGRAM_FILENAME, dest);
            combine_the_files(PROGRAM_FILENAME, dest);

            strcat(buffer, dest);
            cache[size_cache++] = strdup(dest);
            flushf();
            
        }else{
            strcat(buffer, argv[i]);
            strcat(buffer, " ");
        }
    }
    last_command(buffer);
    for(int i = 0 ; i < size_cache; i++){
        delete_file(cache[i]);
    }

    return 0;
}
