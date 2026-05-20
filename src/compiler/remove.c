#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/pc_error.h"
#include "data.h"

void remove_string_from_file(const char *filename, const char *target, int isloop) {

    FILE *src = fopen(filename, "r");
    if (!src) {
        __pc_error__("Error while removing the string from the file %s", filename);
        return;
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if (!temp) {
        __pc_error__("Error while creating the temporary file for removing the string from the file tempfile.txt");
        fclose(src);
        return;
    }

    char line[2048];
    size_t len = strlen(target);
    int removed_once = 0;

    while (fgets(line, sizeof(line), src)) {
        char *read_ptr = line;
        char *pos;

        // printf("%s", line);
        
        while ((pos = strstr(read_ptr, target)) != NULL) {
            if (isloop == 0 && removed_once) {
                break; // Stop removing further if isloop == 0 and one removal is done
            }

            memmove(pos, pos + len, strlen(pos + len) + 1);
            removed_once = 1;

            if (isloop == 0) break;
        }

        fputs(line, temp);
    }

    fclose(src);
    fclose(temp);

    // Replace original file with modified one
    if (remove(filename) != 0) __pc_error__("Error while removing the file named %s", filename);
    if (rename("tempfile.txt", filename) != 0) __pc_error__("Error while renaming the file named tempfile.txt to %s", filename);
}
