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

static inline int new_file_name(char *src, char *name, char *dest){
    if(src == NULL) return 0;

    FILE *f = fopen(src, "r");    
    if(f == NULL) return 0; // It's not file


    strcpy(name, src);
    char *point = strstr(name, ".");
    if(point == NULL) point = name + strlen(name);
    char *ext;
    strcpy(ext, point);
    *point = '\0';
    strcpy(dest, name);
    strcat(dest, "ex");
    if(strcmp(ext, ".ex") == 0){
        strcat(dest, ".c");;
    }else{
        strcat(dest, ext);
    }
    strcat(dest, " ");

    return 1;
}

static inline int last_command(char *command){
    int result = system(command);

    if (result == 0) {
        printf("Compilation successful. Executable created as 'out'.\n");
    } else {
        printf("Compilation failed.\n");
    }
}

#define BUFFER_MAX 1024
#define FILE_NAME_MAX 1024


int main(int argc, char *argv[]){
    char buffer[1024] = "";
    char *cache[1024];
    int size_cache = 0;
    if(argc < 3) return 1;
    for(int i = 1; i < argc; i++){
        char *src = strdup(argv[i]);
        char name[FILE_NAME_MAX];
        char dest[FILE_NAME_MAX];
        printf("file %d: %s", i, argv[i]);
        if(new_file_name(src, name, dest)){
            printf(" -> %s\n", dest);
            strcat(buffer, dest);

            lexf(argv[i], LEX_HANDLING_FILENAME);
            parsef(LEX_HANDLING_FILENAME, PARSE_HANDLING_FILENAME);
            compilef(PARSE_HANDLING_FILENAME, dest);
            strcpy(cache[size_cache++], dest);
            flushf();
            
        }else{
            puts("\n");
            strcat(buffer, argv[i]);
            strcat(buffer, " ");
        }
    }
    printf("last command: %s\n", buffer);
    last_command(buffer);
    for(int i = 0 ; i < size_cache; i++){
        delete_file(cache[i]);
    }
    return 0;
}
