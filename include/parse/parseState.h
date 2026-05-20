#ifndef PARSESTATE_H
#define PARSESTATE_H


struct parseState{
    int method_line_num;
    int method_token_num;
    char *working_identifier;
};

static inline struct parseState init_parseState(char *wi){
    struct parseState ps;
    ps.method_line_num = 0;
    ps.method_token_num = 0;
    ps.working_identifier = wi;
    return ps;
}

#endif