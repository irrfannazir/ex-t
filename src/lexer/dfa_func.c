#include <stdio.h>
#include "lex/dfah.h"

int dfa_new_token(const char *fn1, const char *fn2, t_type value){
    FILE *fp1 = fopen(fn1, "a");
    FILE *fp2 = fopen(fn2, "a");
    if (fp1 == NULL) {
        printf("Error opening file for concatenation.\n");
        return 1;
    }
    fprintf(fp1, "0 %d\n", value);
    fputc('\n', fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int dfa_string_conc(const char *filename, char c){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for concatenation.\n");
        return 1;
    }
    fputc(c, fp);
    fclose(fp);
    return 0;
}

int dfa_new_line(const char *filename, int indent){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for concatenation.\n");
        return 1;
    }
    fprintf(fp, "1 %d\n", indent);
    fclose(fp);
    return 0;
}