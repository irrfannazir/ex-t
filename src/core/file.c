#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "common/fileh.h"
#include "common/pc_error.h"
#include "parse/comment.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

#define MAX_WORD_LENGTH 256
#define MAX_LINE_LENGTH MAX_WORD_LENGTH*10

static int ensure_parent_directory(const char *filename) {
    const char *last_slash = strrchr(filename, '/');
    const char *last_backslash = strrchr(filename, '\\');
    const char *separator = last_slash;

    if (last_backslash && (!separator || last_backslash > separator)) {
        separator = last_backslash;
    }
    if (!separator) return 0;

    size_t len = (size_t)(separator - filename);
    if (len == 0 || len >= MAX_LINE_LENGTH) return 0;

    char directory[MAX_LINE_LENGTH];
    memcpy(directory, filename, len);
    directory[len] = '\0';

    if (MKDIR(directory) != 0 && errno != EEXIST) {
        __pc_error__("Error creating directory named %s", directory);
        return 1;
    }
    return 0;
}

int create_file(const char *filename, const char *content) {
    if (ensure_parent_directory(filename)) return 1;

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
        free(temp);
        __pc_error__("Error while reading file named %s\n", filename);
        return NULL;
    }
    if (!temp) {
        fclose(file);
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
    if (n < 0) return temp;
    free(temp);
    return NULL;
}


char *read_nth_content_werror(const char *filename, int n){
    FILE *file = fopen(filename, "r");
    char *temp = malloc(1024 * sizeof( char ));
    if(!file){
        free(temp);
        __pc_error__("Error while reading file named %s\n", filename);
        return NULL;
    }
    if (!temp) {
        fclose(file);
        return NULL;
    }

    while(fgets(temp, 1024, file)) {
        if(is_inline_comment(temp)) continue;

        n--;

        if (n < 0) break;
    }

    fclose(file);
    if (n < 0) return temp;
    free(temp);
    return NULL;
}

int delete_file(const char *filename){
    if(remove(filename) != 0){
        perror("Error on real-time data alteration");
        return 1;
    }
    return 0;
}
