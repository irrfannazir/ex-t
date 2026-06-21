#ifndef COMPILEH_H
#define COMPILEH_H

#include "common/default.h"
#include "compile/cfh.h"

#define C_PROGRAM_MAX 500

int *line_to_int_array(const char *line, int *count);
void compile_file(const char *filename, const char *outfile);
void add_the_header(const char *filename, const char *headername);
char *serialize(int start, int end);
const char *find_datatype(int index);

void declaration_exec(const char *fn, int *arr, int count);
void assign_exec(const char *dfn, int *arr, int count);
void block_paradigm(const char *fn, char *keyword, int *arr, int count);
void else_condition(const char *fn);
void for_condition(const char *fn, int *arr, int count);
void print_statement(const char *ffn, const char *fn, int *arr, int count);

#endif