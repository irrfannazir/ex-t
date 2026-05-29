#ifndef SYNTAX_COMMENT_H
#define SYNTAX_COMMENT_H


#define SYNTAX_COMMENT_TOKEN "//"
#define SYNTAX_FUNCTION_TOKEN "$$"

static inline int is_inline_comment(const char *str){
    if(!str) return 0;
    return str[0] == '/' && str[1] == '/';
}

static inline int is_inline_function(const char *str){
    if(!str) return 0;
    return str[0] == '$' && str[1] == '$';
}


#endif