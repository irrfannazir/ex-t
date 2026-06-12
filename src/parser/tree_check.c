#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/pdebug.h"
#include "parse/syntax.h"
#include "common/pc_error.h"

int ssn;

static inline size_t slice_new_line(char *line) {
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == '\t'))
        line[--len] = '\0';
    return len;
}


static inline char* get_nth_colon_line(int n) {
    FILE* file = fopen(SYNTAX_DIRECTORY, "r");
    if (!file){
        __pc_error__("Error while retrieving syntax from file with directory named %s", SYNTAX_DIRECTORY);
        exit(1);
    }

    char line[1024];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        size_t len = slice_new_line(line);

        // Check if line ends with ':'
        if (len > 0 && line[len - 1] == ':') {
            count++;
            if (count == n) {
                line[len - 1] = '\0'; // Remove the colon
                fclose(file);
                return strdup(line); // Return a copy of the string
            }
        }
    }

    fclose(file);
    return NULL; // If nth line ending with ':' not found
}


int does_tree_needed(char *word){
    ssn = 1;
    char *ss = get_nth_colon_line(ssn);
    ssn++;
    while(ss != NULL){
        #ifdef P_CHECKING_WORD
          printf("Checking the word %s == %s\n", ss, word);
        #endif
        if(strcmp(word, ss) == 0){
            return 1;
        }
        ss = get_nth_colon_line(ssn);
        ssn++;
    }
    return 0;
}
