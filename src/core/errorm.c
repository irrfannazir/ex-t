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

int printError(const char *filename){
    FILE *fh = fopen(filename, "r");
    char line[LINE_MAX];
    while(fgets(line, LINE_MAX, fh)) printf("%s", line);
    fclose(fh);
    fh = fopen(filename, "w");
    fclose(fh);
}
