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


int pushError(const char *fn, const float priority, const char *msg, ...){
    FILE *fh = fopen(fn, "a");
    va_list args;
    va_start(args, msg);
    fprintf(fh, "%f ", priority);
    vfprintf(fh, msg, args);
    printf("\n");
    va_end(args);
    fclose(fh);
    return 1;
}

#define LINE_MAX 1024

int printError(const char *filename, int lsn){
    FILE *fh = fopen(filename, "r");
    if (!fh) return 1;
    char line[LINE_MAX] = "";
    char msg[LINE_MAX] = "";
    char record[LINE_MAX] = "";
    float max = 0;
    float priority = 0;
    printf("Error (%d): ", lsn);
    while(fgets(record, sizeof(record), fh)){
        line[0] = '\0';
        if(sscanf(record, "%f %1023[^\n]", &priority, line) != 2) continue;
        if(max < priority){
            snprintf(msg, sizeof(msg), "%s\n", line);
            max = priority;
        }else if(max == priority){
            size_t used = strlen(msg);
            snprintf(msg + used, sizeof(msg) - used, "%s", line);
        }
    }
    if(strcmp(msg, "") == 0){
        printf("Invalid Syntax\n");
    }else{
        printf("%s\n", msg);
    }
    fclose(fh);
    fh = fopen(filename, "w");
    fclose(fh);
    return 0;
}
