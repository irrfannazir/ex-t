#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "common/fileh.h"
#include "common/pc_error.h"
#include "parse/comment.h"

#define MAX_WORD_LENGTH 256
#define MAX_LINE_LENGTH MAX_WORD_LENGTH*10

void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if ( !file ) {
        __pc_error__("Error creating file named %s", filename);
        return;
    }
    
    if (content) {
        if (fputs(content, file) == EOF) {
            __pc_error__("Error writing content to file %s", filename);
        }
    }
    
    if (fclose(file) != 0) {
        __pc_error__("Error closing file %s", filename);
    }
}

void print_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
}

char *read_nth_content_from_file(const char *filename, int n){
    FILE *file = fopen(filename, "r");
    char *temp = malloc(1024 * sizeof( char ));
    if(!file){
        __pc_error__("Error while reading file named %s\n", filename);
        return NULL;
    }

    while(fgets(temp, 1024, file)) {
        if(is_inline_comment(temp)){
            continue;
        }
        n--;

        if (n < 0) break;
    }

    fclose(file);
    return temp;
}