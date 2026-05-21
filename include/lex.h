#ifndef LEX_H
#define LEX_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static inline char *get_extension(char *name){
    char *point = strstr(name, ".");
    if(point == NULL) point = name + strlen(name); // No extension found

    char *ext = strdup(point);
    *point = '\0'; // trimmed name

    return ext;
}

static inline int new_file_name(const char *src){
    if(src == NULL) return 0;
    
    FILE *f = fopen(src, "r");    
    if(f == NULL) return 0; // It's not file
    fclose(f);

    return 1;
}

static inline get_dest_filename(char *src){
    char *name = strdup(src);
    char *ext = get_extension(name);

    if(strcmp(ext, ".ex") == 0){
        sprintf(dest, "%sex.c ", name);
    }else{
        sprintf(dest, "%sex%s ", name, ext);
    }
}

int lexf(const char *ex_filename, const char *dest_filename);

#endif