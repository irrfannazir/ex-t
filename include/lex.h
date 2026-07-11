#ifndef LEX_H
#define LEX_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PGM_FINAL "--after-ex-convertion--"
#define FILE_NAME_MAX 1024

static inline char *get_extension(char *name){
    char *point = strrchr(name, '.');
    if(point == NULL) point = name + strlen(name); // No extension found
    return point;
}

static inline int new_file_name(const char *src){
    if(src == NULL) return 0;
    
    FILE *f = fopen(src, "r");    
    if(f == NULL) return 0; // It's not file
    fclose(f);

    return 1;
}

static inline int get_dest_filename(char *dest, const char *src){ 
    char name[FILE_NAME_MAX];
    snprintf(name, sizeof(name), "%s", src);

    char *ext = get_extension(name);
    if(strcmp(ext, ".ex") == 0){
        *ext = '\0';
        snprintf(dest, FILE_NAME_MAX, "%s%s.c", name, PGM_FINAL);
        return 0;
    }

    snprintf(dest, FILE_NAME_MAX, "%s%s%s", name, PGM_FINAL, ext);
    return 1;
}

int lexf(const char *ex_filename, const char *dest_filename, int isinline);

#endif
