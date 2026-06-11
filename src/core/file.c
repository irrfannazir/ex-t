#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "common/fileh.h"
#include "common/pc_error.h"
#include "parse/comment.h"

#define MAX_WORD_LENGTH 256
#define MAX_LINE_LENGTH MAX_WORD_LENGTH*10

int create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if ( !file ) {
        __pc_error__("Error creating file named %s", filename);
        return 1;
    }
    
    if (content) {
        if (fputs(content, file) == EOF) {
            __pc_error__("Error writing content to file %s", filename);
            return 1;
        }
    }
    
    if (fclose(file) != 0) {
        __pc_error__("Error closing file %s", filename);
        return 1;
    }
    return 0;
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

int delete_file(const char *filename){
    if(remove(filename) != 0){
        perror("Error on real-time data alteration");
        return 1;
    }
    return 0;
}