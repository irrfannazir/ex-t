#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "lex/lfh.h"
#include "common/constants.h"

#define LEX_HANDLING_FILENAME "lex.txt"
#define PARSE_HANDLING_FILENAME "parse.txt"
#define PGM_FINAL "ex"


#define BUFFER_MAX 1024
#define FILE_NAME_MAX 1024

static int run_the_compiler(const char *src, char *dest){
    lexf(src, LEX_HANDLING_FILENAME);
    parsef(LEX_HANDLING_FILENAME, PARSE_HANDLING_FILENAME);
    compilef(PARSE_HANDLING_FILENAME, dest);
}

int main(int argc, char *argv[]){
    char buffer[1024] = "";
    char *cache[1024];
    int size_cache = 0;
    if(argc < 3) return 1;
    for(int i = 1; i < argc; i++){
        if(new_file_name(argv[i])){
            char *dest = get_dest_filename(argv[i]);
            run_the_compiler(argv[i], dest);
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
