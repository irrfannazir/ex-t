#include <stdio.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "common/constants.h"

#define LEX_HANDLING_FILENAME "lex.txt"
#define PARSE_HANDLING_FILENAME "parse.txt"
#define IC_FILENAME "pgm.c"



int main(int argc, char *argv[]){
    const int8_t isinput = argc == 1;
    lexf(isinput, argv[1], LEX_HANDLING_FILENAME);
    parsef(LEX_HANDLING_FILENAME, PARSE_HANDLING_FILENAME);
    compilef(PARSE_HANDLING_FILENAME, IC_FILENAME);
    flushf();
    return 0;
}
