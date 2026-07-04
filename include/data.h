#ifndef DATA_H
#define DATA_H
#include "lex/dfah.h"
#include "lex/lfn.h"
#include "common/constants.h"
/*
    This is the file where all the global data which is commonly used for lex, parse, compile.
*/


//limits
#define DIGIT 20
#define TOKEN_STRING_MAX 500
#define LEX_LINE_MAX TOKEN_STRING_MAX + DIGIT + 1
#define PARSE_LINE_MAX 1024
#define PSUEDO_CODE_MAX 1024

#define NAME_STRLEN 1024

//filename
#define PARSING_HANDLING_FILE_NAME    "parse.txt"
#define PARSED_INFORMATION            "parse.info"
#define DEFINED_IDENTIFIER_FILE_NAME  "symtab.bin"
#define PARSE_DATATYPE_LIST_FILE_NAME "grammar/datatype.txt"
#define PARSE_KEYWORD_LIST_FILE_NAME  "grammar/keywords.bin"


// flush
#ifdef DELETE_UNWANTED_FILES
  static char *unwanted_filenames[] = {
    "lex.txt",
    PARSING_HANDLING_FILE_NAME,
    DEFINED_IDENTIFIER_FILE_NAME,
  };
#endif
  
  

extern int dont_compile;


//functions
int get_indentation(int index);
char *get_token(int index);
t_type get_type(int index);
void get_type_token(int index, t_type *type, char str[TOKEN_STRING_MAX]);




#endif
