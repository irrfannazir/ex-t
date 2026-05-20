#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/perror.h"
#include "common/fileh.h"
#include "data.h"

char working_identifier[NAME_STRLEN] = "";

void parsef(const char *src_filename, const char *dest_filename) {
    printf("Parsing the tokens.\n");
    create_file(dest_filename, NULL);
    create_file(DEFINED_IDENTIFIER_FILE_NAME, "");

    int method_line_num = 0;
    int method_token_num = 0;

    while (1) {
        char *word = get_word_from_method(method_line_num, method_token_num);
        int index = get_index_from_lex(1);

        log_debug("Analysing %s and %s\n", word, get_token(index));

        if (get_token(index) == NULL && word == NULL) {
            skip_to_next_line(&method_line_num, &method_token_num);
            log_debug("\tSkipping to next line.\n");

            if (!get_token(get_index_from_lex(0))) {
                log_debug("End of parsing\n");
                return;
            }
            continue;
        }

        if (index == -1 || word == NULL) {
            if (handle_missing_word_or_token(word, index, &method_line_num, &method_token_num)) {
                continue; // error already reported, continue parsing
            }
            log_debug("\tSkipping to next method\n");
            skip_to_next_method(&method_line_num, &method_token_num);
            continue;
        }

        if (word == NULL && (index == -1 || method_token_num == 0)) {
            report_method_error(method_line_num);
            dont_compile = 1;

            if (skip_to_next_line(&method_line_num, &method_token_num)) {
                log_debug("End of file.\n");
                break;
            }
            continue;
        }

        if (index == -1 || get_token(index) == NULL) {
            skip_to_next_method(&method_line_num, &method_token_num);
            continue;
        }

        handle_identifier_declaration(index, method_line_num);

        if (try_match_type(word, index, &method_token_num)) {
            continue;
        }
        if (try_match_word(word, index, &method_token_num)) {
            continue;
        }
        if (does_tree_needed(word)) {
            if (handle_syntax_tree(word, index, &method_line_num, &method_token_num)) {
                continue;
            }
        } else {
            log_debug("\tNot this syntax\n");
            skip_to_next_method(&method_line_num, &method_token_num);
        }

        clear_identifier_buffer();
    }
}

