#include <stdio.h>
#include <string.h>

int size_of_last_line(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char c;
    int size = 0;
    while ((c = fgetc(fp)) != -1) {
        if (c == '\n'){
            size = 0;
        }else{
            size++;
        }
    }

    fclose(fp);
    return size + 2;
}

int fget_last_line(const char *filename, char *last_line, int size){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[size];
    
    while (fgets(line, size, fp)) {
        snprintf(last_line, size, "%s", line);
    }

    fclose(fp);
    last_line[strcspn(last_line, "\n")] = '\0';

    return 0;
}
