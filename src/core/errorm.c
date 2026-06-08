#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int ReadLine(const char *filename, char *line, int size, int ln){
    FILE *fh = fopen(filename, "r");
    if (!fh) return 1;
    while (fgets(line, size, fh) && ln > 1) ln--;
    fclose(fh);
    return 0;
}


int pushError(const char *fn, const int priority, const char *msg, ...){
    FILE *fh = fopen(fn, "a");
    va_list args;
    va_start(args, msg);
    fprintf(fh, "%d ", priority);
    fprintf(fh, msg, args);
    fprintf(fh, "\n");
    va_end(args);
    fclose(fh);
}

#define LINE_MAX 1024

int printError(const char *filename, const char *default_msg){
    FILE *fh = fopen(filename, "r");
    char line[LINE_MAX];
    char msg[LINE_MAX] = "";
    int max = 0;
    int priority = 0;
    while(fscanf(fh, "%d %[^\n]s", &priority, line) == 2){
        if(max <= priority){
            strcpy(msg, line);
            max = priority;
        }
    }
    if(msg[0] == '\0') strcpy(msg, default_msg);
    printf("%s\n", msg);
    fclose(fh);
    fh = fopen(filename, "w");
    fclose(fh);
}
