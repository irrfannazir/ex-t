#include <stdlib.h>
#include <stdio.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "data.h"

void process_parametres(const char *ffn, const char *pfn, int *arr, int count){
    switch(arr[0]){
        case 0:
            declaration_exec(pfn, arr, count);
            break;
        case 3:
            block_paradigm(pfn, "if", arr, count);
            break;
        case 4:
            block_paradigm(pfn, "else if", arr, count);    
            break;
        case 5:
            else_condition(pfn);
            break;
        case 6:
            for_condition(pfn, arr, count);
            break;
        case 7:
            block_paradigm(pfn, "while", arr, count);
            break;
        case 9:
            print_statement(ffn, pfn, arr, count);
            break;
    }
}

void add_the_program(const char *pfn, const char *ffn, const char *efn){
    int i = 0;
    char *parsed_data = get_nth_line(pfn, i, NULL);
    int indent_tab_number = 0;
    i++;
    while(parsed_data != NULL){
        trim_newline(parsed_data);
        if(get_indentation(i - 2) < get_indentation(i - 1)){
            if(indent_tab_number == 0){
                indent_tab_number = get_indentation(i - 1) - get_indentation(i - 2);
            }
        }
        int count;
        int *arr = line_to_int_array(parsed_data, &count);
        process_parametres(ffn, efn, arr, count);
        parsed_data = get_nth_line(PARSING_HANDLING_FILE_NAME, i, NULL);
        i++;
        if( ( get_indentation(i - 3) - indent_tab_number == get_indentation(i - 2) ) && indent_tab_number != 0){
            remove_string_from_file(efn, PGM_CURSOR, 0);
        }
        free(arr);
    }
}


int compilef(const char *src_filename, const char *final_filename, const char *dest_filename){
    if(dont_compile) return 1;
    printf("Compiling the program.\n");
    create_file(dest_filename, DEFAULT_PROGRAM);
    add_the_program(src_filename, final_filename, dest_filename);
    printf("********The output program implemented in C programming Language********\n\n");
    remove_string_from_file(dest_filename, PGM_CURSOR, 1);
    remove_string_from_file(final_filename, FUNCTION_CURSOR, 1);
    remove_string_from_file(final_filename, INCLUDE_CURSOR, 1);
    print_file_content(dest_filename);
    printf("\n\n\n");
    return 0;
}
