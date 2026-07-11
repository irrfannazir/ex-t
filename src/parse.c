#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "parse/parseh.h"
#include "parse/perror.h"
#include "common/fileh.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "data.h"

char working_identifier[NAME_STRLEN] = "";

int parsef(const char *dest_filename) {
    printf("Parsing the tokens.\n");
    if (create_file(dest_filename, NULL)) return 1;
    if (create_file(DEFINED_IDENTIFIER_FILE_NAME, "")) return 1;
    if (create_file(ERROR_HANDLING_FILENAME, "")) return 1;

    int method_line_num = 0;
    int method_token_num = 0;

    char *word;
    int index;

    if(get_type(get_index_from_lex(1)) == TOKEN_NULL) skip_to_next_line(&method_line_num, &method_token_num);

    while (1) {
        word = get_word_from_method(method_line_num, method_token_num);
        index = get_index_from_lex(1);
        char *token = get_token(index);

        log_debug("Analysing %s and %s (%d)\n", word, token, index);
        unsigned char flag = FLAGS_TO_INT(unsigned char,
            token == NULL,
            index == -1,
            word == NULL
        );
        log_debug("Flag: %d%d%d\n",
            token == NULL,
            index == -1,
            word == NULL
        );

        switch(flag){
            case 0b001:
                if(method_token_num == 0){
                    log_debug("\tSkipping to next line.\n");
                    printError(ERROR_HANDLING_FILENAME, num_lines(lsn));
                    skip_to_next_line(&method_line_num, &method_token_num);
                    free(token);
                    free(word);
                    continue;
                }
                report_method_error(method_line_num);
                skip_to_next_method(&method_line_num, &method_token_num);
                free(token);
                free(word);
                continue;
            case 0b110:
                log_debug("\tSkipping to next method\n");
                pushError(ERROR_HANDLING_FILENAME, method_line_num, "%s is unexpected", token ? token : "");
                skip_to_next_method(&method_line_num, &method_token_num);
                free(token);
                free(word);
                continue;
            case 0b111:
                log_debug("\tSkipping to next line.\n");
                skip_to_next_line(&method_line_num, &method_token_num);
                free(token);
                free(word);
                continue;
            case 0b100:
            case 0b101:
                log_debug("End of parsing\n");
                free(token);
                free(word);
                return dont_compile ? 1 : 0;
        }


        handle_identifier_declaration(index, method_line_num);
        handle_undeclared_variable(index);
        
        if (try_match_type(word, index, &method_token_num)) {
            free(token);
            free(word);
            continue;
        }
        if (try_match_word(word, index, &method_token_num)) {
            free(token);
            free(word);
            continue;
        }
        if (does_tree_needed(word)) {
            if (handle_syntax_tree(word, index, &method_line_num, &method_token_num)) {
                free(token);
                free(word);
                continue;
            }
        } else {
            log_debug("\tNot this syntax\n");
            skip_to_next_method(&method_line_num, &method_token_num);
        }

        clear_identifier_buffer();
        free(token);
        free(word);
    }

    return dont_compile ? 1 : 0;
}

