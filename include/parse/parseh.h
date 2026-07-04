#ifndef PARSEH_H
#define PARSEH_H
#include "data.h"

#define PARSE_ERROR_MESSAGE_SIZE 100


extern int error_priority;
extern int current_error_priority;
extern char *error;
extern char working_identifier[NAME_STRLEN];
extern int lsn;
extern int ltn;

void push_to_parse_string(int index);
char *get_word_from_method(int line_number, int token_number);
char *get_error_message_from_method(int line_number);
char *get_function_name_from_method(int line_number);
int get_index_from_lex(int cl); //Returns -1 if the type is EOF
int skip_to_next_line(int *mln, int *mtn); // Moves to next line in lex
int next_token(int *mln); // Moves to next token for both
int skip_to_next_method(int *mln, int *mtn); // Moves to next method checking
int token_to_type(char *syn);
int does_tree_needed(char *word); //Is word contains and ending with ':'
int parsing_tree_analysis(char *format, int start, int size); //Here is the function for parsing
int fputs_with_newl(const char *filename, const char *str); //Append string into the filename

void push_error(const char *temp);
int print_error();

void report_method_error(int method_line_num);
void handle_identifier_declaration(int index, int method_line_num);
void handle_undeclared_variable(int index);
int try_match_type(char *word, int index, int *method_token_num);
int try_match_word(char *word, int index, int *method_token_num);
int handle_syntax_tree(char *word, int index, int *method_line_num, int *method_token_num);
void clear_identifier_buffer();

static inline int compare_the_word(char *word, char *token){
    return strcmp(word, token) == 0;
}


#endif
