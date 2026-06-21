#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/pdebug.h"
#include "parse/syntax.h"
#include "common/pc_error.h"

static inline size_t slice_new_line(char *line) {
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == '\t'))
        line[--len] = '\0';
    return len;
}

int does_tree_needed(const char *word) {
    FILE *file = fopen(SYNTAX_DIRECTORY, "r");
    if (!file) {
        __pc_error__("Error while retrieving syntax from file with directory named %s",
                     SYNTAX_DIRECTORY);
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        size_t len = slice_new_line(line);
        if (len > 0 && line[len - 1] == ':') {
            line[len - 1] = '\0';          // remove colon
            if (strcmp(word, line) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}