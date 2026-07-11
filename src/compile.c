#include <stdlib.h>
#include <stdio.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "data.h"

void process_parametres(const char *ffn, const char *pfn, int *arr, int count){
    if (!arr || count <= 0) return;
    switch(arr[0]){
        case INSTRUCTION_DECLARATION:
        case INSTRUCTION_DECLARATION_WITHOUT_ASSIGNMENT:
            declaration_exec(pfn, arr, count);
            break;
        case INSTRUCTION_ASSIGNMENT:
            assign_exec(pfn, arr, count);
            break;
        case INSTRUCTION_IF_BLOCK:
            block_paradigm(pfn, "if", arr, count);
            break;
        case INSTRUCTION_ELSE_IF_BLOCK:
            block_paradigm(pfn, "else if", arr, count);    
            break;
        case INSTRUCTION_ELSE_BLOCK:
            else_condition(pfn);
            break;
        case INSTRUCTION_FOR_BLOCK:
            for_condition(pfn, arr, count);
            break;
        case INSTRUCTION_WHILE_BLOCK:
            block_paradigm(pfn, "while", arr, count);
            break;
        case INSTRUCTION_PRINT:
            print_statement(ffn, pfn, arr, count);
            break;
        default:
            fprintf(stderr, "Unknown instruction code: %d\n", arr[0]);
            break;
    }
}

static int instruction_opens_block(int instruction) {
    return instruction == INSTRUCTION_IF_BLOCK ||
           instruction == INSTRUCTION_ELSE_IF_BLOCK ||
           instruction == INSTRUCTION_ELSE_BLOCK ||
           instruction == INSTRUCTION_FOR_BLOCK ||
           instruction == INSTRUCTION_WHILE_BLOCK;
}

static void close_generated_block(const char *efn) {
    remove_string_from_file(efn, PGM_CURSOR, 0);
    fputs_with_newl(PARSED_INFORMATION, "end of the finally mentioned block");
}

void add_the_program(const char *pfn, const char *ffn, const char *efn){
    enum { MAX_BLOCK_DEPTH = 128 };
    int block_stack[MAX_BLOCK_DEPTH];
    int block_depth = 0;
    int i = 0;
    char *parsed_data = get_nth_line(pfn, i, NULL);

    while(parsed_data != NULL){
        trim_newline(parsed_data);

        int current_indent = get_indentation(i);
        while (block_depth > 0 && current_indent <= block_stack[block_depth - 1]) {
            close_generated_block(efn);
            block_depth--;
        }

        int count;
        int *arr = line_to_int_array(parsed_data, &count);
        int opens_block = arr && count > 0 && instruction_opens_block(arr[0]);
        process_parametres(ffn, efn, arr, count);
        free(parsed_data);

        int next_indent = get_indentation(i + 1);
        if (opens_block && next_indent > current_indent) {
            if (block_depth < MAX_BLOCK_DEPTH) {
                block_stack[block_depth++] = current_indent;
            } else {
                fprintf(stderr, "Maximum block nesting depth exceeded.\n");
            }
        }
        free(arr);

        i++;
        parsed_data = get_nth_line(pfn, i, NULL);
    }

    while (block_depth > 0) {
        close_generated_block(efn);
        block_depth--;
    }
}


int compilef(const char *src_filename, const char *final_filename, const char *dest_filename){
    if(dont_compile) return 1;
    printf("Compiling the program.\n");
    if (create_file(dest_filename, DEFAULT_PROGRAM)) return 1;
    if (create_file(PARSED_INFORMATION, "")) return 1;
    add_the_program(src_filename, final_filename, dest_filename);
    printf("********The output program implemented in C programming Language********\n\n");
    remove_string_from_file(dest_filename, PGM_CURSOR, 1);
    remove_string_from_file(final_filename, FUNCTION_CURSOR, 1);
    remove_string_from_file(final_filename, INCLUDE_CURSOR, 1);
    print_file_content(dest_filename);
    printf("\n\n\n");
    return 0;
}
