#include "lex/lexh.h"
#include "lex/dfah.h"
#include "lex/lastl.h"

t_type lexeme_of_last_line(const char *filename) {

    int size = size_of_last_line(filename);
    if (size == 0) return TOKEN_EOF;
    char last_line[size];
    if (!fget_last_line(filename, last_line, size)){
        if (iskeyword(last_line)) return TOKEN_KEYWORD;
        if (isdatatype(last_line)) return TOKEN_DATATYPE;
    }

    return TOKEN_IDENTIFIER;
}