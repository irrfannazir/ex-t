#include "lex/lfh.h"
#include "compile/cfh.h"
#include "common/default.h"
#include "common/pc_error.h"
#include <stdio.h>
#include <stdlib.h>



static inline int read_file(const char *fn, char **content) {
    FILE *file = fopen(fn, "rb");
    if (file == NULL) {
        __pc_error__("Error opening file %s", fn);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size < 0) {
        perror("Error determining file size");
        fclose(file);
        return 1;
    }
    
    *content = (char *)malloc(file_size + 1);
    if (*content == NULL) {
        __pc_error__("Memory allocation failed");
        fclose(file);
        return 1;
    }
    
    size_t bytes_read = fread(*content, 1, file_size, file);
    if (bytes_read < (size_t)file_size && ferror(file)) {
        __pc_error__("Error reading file %s", fn);
        free(*content);
        *content = NULL;
        fclose(file);
        return 1;
    }

    (*content)[bytes_read] = '\0';
    fclose(file);
    return 0;
}

int combine_the_files(char *fn1, char * fn2){
    char *content = NULL;
    if (read_file(fn2, &content)) return 1;
    insert_before_target(fn1, content, EXPGM_CURSOR);
    remove_string_from_file(fn1, EXPGM_CURSOR, 1);
    free(content);
    if (delete_file(fn2)) return 1;
    if(rename(fn1, fn2)) {
        __pc_error__("Error while renaming %s to %s", fn1, fn2);
        return 1;
    }
    return 0;
}
