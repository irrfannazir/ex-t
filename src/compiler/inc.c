#include <stdio.h>
#include <string.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "common/fileh.h"
#include "data.h"

void add_the_header(const char *filename, const char *headername){
    static char temp[C_PROGRAM_MAX] = "";
    int i = 1;
    int flag = 0;
    sprintf(temp, "#include <%s>\n", headername);
    while(get_nth_line(filename, i, NULL)){
        if(strcmp(get_nth_line(filename, i, NULL), temp) == 0){
            flag = 1;
            break;
        }
        i++;
    }
    if(!flag){
        insert_before_target(filename, temp, INCLUDE_CURSOR);
    }
}