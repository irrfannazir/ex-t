#ifndef COMPILEH_H
#define COMPILEH_H

#define DEFAULT_PROGRAM "$$include_cursor; $$function_cursor;int main(){$$program_cursor;return 0;}"
#define PGM_CURSOR "$$program_cursor;"
#define FUNCTION_CURSOR "$$function_cursor;"
#define INCLUDE_CURSOR "$$include_cursor;"
#define C_PROGRAM_MAX 500

int *line_to_int_array(const char *line, int *count);
void compile_file(const char *filename, const char *outfile);
void add_the_header(const char *filename, const char *headername);
char *serialize(int start, int end);
void remove_string_from_file(const char *filename, const char *target, int isloop);
const char *find_datatype(int index);

void declaration_exec(const char *fn, int *arr, int count);
void block_paradigm(const char *fn, char *keyword, int *arr, int count);
void else_condition(const char *fn, int *arr, int count);
void for_condition(const char *fn, int *arr, int count);
void print_statement(const char *fn, int *arr, int count);

#endif