#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "lex/lfh.h"
#include "lex/lfn.h"
#include "common/constants.h"
#include "data.h"

int combine_the_files(char *fn1, char * fn2);

extern int dont_compile;

int main(int argc, char *argv[]){
    char *command_args[1024];
    char *cache[1024];
    int size_cache = 0;
    int command_count = 0;
    int exit_status = 0;
    if(argc < 3) return 1;
    for(int i = 1; i < argc; i++){
        if(new_file_name(argv[i])){ 
            char dest[FILE_NAME_MAX];
            const int isinline = get_dest_filename(dest, argv[i]);
            int status = lexf(argv[i], LEX_HANDLING_FILE_NAME, isinline);
            if (status) {
                exit_status = status;
                flushf();
                goto cleanup;
            }

            status = parsef(PARSING_HANDLING_FILE_NAME);
            if (status || dont_compile) {
                exit_status = status ? status : 1;
                flushf();
                goto cleanup;
            }

            status = compilef(PARSING_HANDLING_FILE_NAME, PROGRAM_FILENAME, dest);
            if (status) {
                exit_status = status;
                flushf();
                goto cleanup;
            }

            status = combine_the_files(PROGRAM_FILENAME, dest);
            if (status) {
                exit_status = status;
                flushf();
                goto cleanup;
            }

            if (command_count >= (int)(sizeof(command_args) / sizeof(command_args[0])) - 1) {
                fprintf(stderr, "Too many command arguments.\n");
                exit_status = 1;
                flushf();
                goto cleanup;
            }
            command_args[command_count++] = strdup(dest);
            if (command_args[command_count - 1] == NULL) {
                fprintf(stderr, "Failed to duplicate generated filename.\n");
                exit_status = 1;
                flushf();
                goto cleanup;
            }
            cache[size_cache++] = command_args[command_count - 1];
            flushf();
        }else{
            if (command_count >= (int)(sizeof(command_args) / sizeof(command_args[0])) - 1) {
                fprintf(stderr, "Too many command arguments.\n");
                exit_status = 1;
                flushf();
                goto cleanup;
            }
            command_args[command_count++] = argv[i];
        }
    }

    if (command_count == 0) {
        goto cleanup;
    }
    command_args[command_count] = NULL;
    if (last_command(command_args) != 0) {
        exit_status = 1;
        goto cleanup;
    }

cleanup:
    for(int i = 0 ; i < size_cache; i++){
        delete_file(cache[i]);
        free(cache[i]);
    }

    return dont_compile ? 1 : exit_status;
}
