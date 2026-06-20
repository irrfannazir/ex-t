#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_line(const char* filename, int n, const char *keyword){
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    const int size = sizeof(char) * 256;
    char *line = malloc(size);
    if(keyword != NULL){
        while(fgets(line, size, file)){
            int line_len = strlen(line);
            if(line[line_len - 1] == '\n' && line[line_len - 2] == ':'){
                line[line_len - 2] = '\0'; 
            }else if(line[line_len - 1] == '\n'){
                line[line_len - 1] = '\0'; 
            }
            if(strcmp(line, keyword) == 0){
                break;
            }
        }
    }

    while (fgets(line, size, file)) {
        if(n == 0){
            fclose(file);
            return line;
        }
        n--;
    }
    fclose(file);
    return NULL;
}

