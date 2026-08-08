#ifndef COMPILEH_H
#define COMPILEH_H

#include "common/default.h"
#include "compile/cfh.h"

#define C_PROGRAM_MAX 4096

typedef enum {
    INSTRUCTION_DECLARATION = 0,
    INSTRUCTION_DECLARATION_WITHOUT_ASSIGNMENT = 1,
    INSTRUCTION_ASSIGNMENT = 2,
    INSTRUCTION_IF_BLOCK = 3,
    INSTRUCTION_ELSE_IF_BLOCK = 4,
    INSTRUCTION_ELSE_BLOCK = 5,
    INSTRUCTION_FOR_BLOCK = 6,
    INSTRUCTION_WHILE_BLOCK = 7,
    INSTRUCTION_PRINT = 8,
    INSTRUCTION_FUNCTION = 9,
    INSTRUCTION_FUNCTION_WITH_ARGS = 10
} InstructionKind;

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
void function_declaration(const char *dfn, int i_name);
void function_declaration_with_args(const char *dfn, int *arr, int count);

#endif
