//dfa


typedef enum{
    TOKEN_EOF,          // 0 End Of File
    TOKEN_IDENTIFIER,   // 1 Identifiers (variables, function names, etc.)
    TOKEN_INTEGER,      // 2 Integer literals (e.g., 123, 456)
    TOKEN_KEYWORD,      // 3 Keywords (e.g., if, for, while, etc.)
    TOKEN_OPERATOR,     // 4 Operators (e.g., +, -, *, /, ==)
    TOKEN_PUNCTUATION,  // 5 Punctuation (e.g., (, ), {, }, ;, ,)
    TOKEN_DATATYPE,     // 6 Datatypes (e.g., single, array)
    TOKEN_EXPRESSION,   // 7 Expressions (e.g., arithmetic, logical)
    TOKEN_STRING,       // 8 String literals (e.g., "Hello")
    TOKEN_NULL          // 9 Null Terminator
} t_type;

t_type lexeme_of_last_line(const char *filename);
int dfa_new_token(const char *fn1, const char *fn2, t_type value);
int dfa_string_conc(const char *filename, char c);
int dfa_new_line(const char *filename, int indent);
int change_to_form(const char *fnw, const char *fn1, const char *fn2);