#ifndef PARSEH_H
#define PARSEH_H
#include "data.h"

#define PARSE_DETAILS_MAX DIGIT*10
#define PARSE_ERROR_MESSAGE_SIZE 100

#define DEFAULT_ERROR_MESSAGE "Invalid Syntax"


extern char parsed_token[PARSE_DETAILS_MAX];
extern int error_priority;
extern int current_error_priority;
extern char *error;
extern char working_identifier[NAME_STRLEN];
extern int lsn;
extern int ltn;

void push_to_parse_string(int index);
char *get_word_from_method(int line_number, int token_number); //Returns NULL if the line of method ends
char *get_error_message_from_method(int line_number);
char *get_function_name_from_method(int line_number);
int get_index_from_lex(int cl); //Returns -1 if the type is EOF
int skip_to_next_line(int *mln, int *mtn); // Moves to next line in lex
int next_token(int *mln); // Moves to next token for both
int skip_to_next_method(int *mln, int *mtn); // Moves to next method checking
int check_the_type(char *word, t_type type);
int append_token_details(int mln); //Saves the index in a file for parsing
int does_tree_needed(char *word); //Is word contains in tree.txt ending with ':'
int parsing_tree_analysis(char *format, int start, int size); //Here is the function for parsing
int fputs_with_newl(const char *filename, const char *str); //Append string into the filename

void push_error(const char *temp);
int print_error();

void report_method_error(int method_line_num);
void handle_identifier_declaration(int index, int method_line_num);
int try_match_type(char *word, int index, int *method_token_num);
int try_match_word(char *word, int index, int *method_token_num);
int handle_syntax_tree(char *word, int index, int *method_line_num, int *method_token_num);
void clear_identifier_buffer();

static inline int compare_the_word(char *word, char *token){
    return strcmp(word, token) == 0;
}


static inline void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


static inline char* itoaf(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}


#endif
