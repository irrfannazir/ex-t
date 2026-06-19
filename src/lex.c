#include "lex/lexh.h"
#include "lex/lfh.h"
#include "lex/lexInfo.h"
#include "lex/dfah.h"
#include "lex/lastl.h"
#include "lex/lfn.h"
#include "lex/d_fh.h"
#include "lex/lerror.h"
#include "common/default.h"
#include "common/pc_error.h"
#include "common/fileh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


const char delimiter = ';';
int dont_compile = 0;


static inline int dfa_char_analysis(char c, int *s, struct lexInfo *li){
    switch(*s){
        case 0: // Start State: After newline
            if(c == ' '){
                (li -> indent)++;
            }else if(c == '\n' || c == delimiter){
                ;
            }else if(is_string_introduced(c)){
                *s = 2;
            }else if(is_char(c)){
                *s = 3;
            }else if(is_digit(c)){
                *s = 4;
            }else if(is_oper(c)){
                *s = 5;
            }else if(is_punct(c)){
                *s = 6;
            }else{
                charerror(c);
                return 1;
            }
    
            if(c != ' ' && c != '\n' && c != delimiter){
                if (!(li -> ignore_newline)) dfa_new_line(DFA_TOKEN_FILENAME, (li -> indent) / sitc);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }
            break;
        case 1: //Space found
            if(c == ' '){
                ;
            }else if(c == '\n' || c == delimiter){
                *s = 0;
                (li -> indent) = 0;
            }else if(is_string_introduced(c)){
                *s = 2;
            }else if(is_char(c)){
                *s = 3;
            }else if(is_digit(c)){
                *s = 4;
            }else if(is_oper(c)){
                *s = 5;
            }else if(is_punct(c)){
                *s = 6;
            }else{
                charerror(c);
                return 1;
            }
    
            if(c != ' ' && c != '\n' && c != delimiter){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }
            break;
        case 2: // String introduced
            dfa_string_conc(DFA_LEXEME_FILENAME, c);
            if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_STRING);
                *s = 0;
            }
            break;
        case 3: // Identifier found
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                (li -> indent) = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_char(c) || is_digit(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
            }else{
                charerror(c);
                return 1;
            }
            break;
        case 4: // Digit found
            if(c == '.'){
                if(li->point == 0){
                    li->point = 1;
                }else{
                    lexerror(c);
                    return 1;
                }
            }
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                *s = 1;
                li->point = 0;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                (li -> indent) = 0;
                li->point = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                li->point = 0;
                *s = 2;
            }else if(is_char(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                int size = size_of_last_line(DFA_LEXEME_FILENAME);
                char last_token[size + 1];
                fget_last_line(DFA_LEXEME_FILENAME, last_token, size + 1);
                const char *text = "Identifier %.*s is recognized as invalid";
                size_t msg_len = snprintf(NULL, 0, text, size, last_token) + 1;
                char error_msg[msg_len];
                snprintf(error_msg, msg_len, text, size, last_token);
                lexerror(error_msg);
                li->point = 0;
                *s = 0;
            }else if(is_digit(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                li->point = 0;
                *s = 5;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                li->point = 0;
                *s = 6;
            }else{
                charerror(c);
                return 1;
            }
            break;
        case 5: // Operator found
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                (li -> indent) = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
            }else{
                charerror(c);
                return 1;
            }
            break;
        case 6: // Punctuator
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                (li -> indent) = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else{
                charerror(c);
                return 1;
            }
            break;
        case -1:
            puts("Lex Terminated!");
            return 1;
    }
    if (c == '{' || c == '(') (li -> ignore_newline) = 1;
    if ( (li -> ignore_newline) && (c == '}' || c == ')') ) (li -> ignore_newline) = 0;
    return 0;
}



int lexf(const char *ex_filename, const char *dest_filename, const int isinline){
    char c;
    int state = 0;
    struct lexInfo li = init_lexInfo();
    int permission = 0;
    create_file(dest_filename, "");
    create_file(DFA_LEXEME_FILENAME, "");
    create_file(DFA_TOKEN_FILENAME, "");
    init_stat();
    if(ex_filename != NULL){
        FILE *file = fopen(ex_filename, "r");
        FILE *fpgm = fopen(PROGRAM_FILENAME, "w");
        fprintf(fpgm, "%s\n", DEFAULT_HEADER_PROGRAM);
        if (!file) {
            delete_file(DFA_TOKEN_FILENAME);
            delete_file(DFA_LEXEME_FILENAME);
            __pc_error__("Error while retrieving program from file named %s", ex_filename);
            return 1;
        }
        while((c = fgetc(file)) != -1){
            if(isinline){
                if(c == LEX_TOKEN_START && fgetc(file) == LEX_TOKEN_START) {
                    if(!permission) fputs(EXPGM_CURSOR, fpgm);
                    permission = !permission;
                    continue;
                }
                if(permission){
                    int status = dfa_char_analysis(c, &state, &li);
                    if (status) break;
                }else{
                    putc(c, fpgm);
                }
            }else{
                int status = dfa_char_analysis(c, &state, &li);
                if (status) break;
            }
        }
	    puts("");
        fclose(file);
        fclose(fpgm);
    }
    printf("\nTokenizing...\n");

    dfa_char_analysis('\n', &state, &li);
    change_to_form(dest_filename, DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME);
    delete_file(DFA_TOKEN_FILENAME);
    delete_file(DFA_LEXEME_FILENAME);
    return 0;
}
