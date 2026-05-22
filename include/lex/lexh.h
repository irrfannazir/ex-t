#ifndef LEXH_H
#define LEXH_H

#define INLINE_PROGRAM_MAX_SIZE 500
#define DFA_LEXEME_FILENAME "dfa_lexeme.txt"
#define DFA_TOKEN_FILENAME "dfa_token.txt"

#define LEX_TOKEN_START '%'


int iskeyword(const char *str);
int isdatatype(const char *str);


static inline int is_string_introduced(char c){
    return (c == '"') || (c == '`');
}

static inline int is_char(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static inline int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

static inline int is_punct(char c) {
    const char *punct = "%(){}[].,:'\"";
    for (int i = 0; punct[i] != '\0'; i++) {
        if (punct[i] == c)
            return 1;
    }
    return 0;
}

static inline int is_oper(char c) {
    const char *operators = "+-*/=<>";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (operators[i] == c)
            return 1;
    }
    return 0;
}


#endif