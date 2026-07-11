#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "common/fileh.h"
#include "data.h"

void add_the_header(const char *filename, const char *headername){
    static char temp[C_PROGRAM_MAX] = "";
    int i = 1;
    int flag = 0;
    if (snprintf(temp, sizeof(temp), "#include <%s>\n", headername) >= (int)sizeof(temp)) {
        return;
    }
    char *line = NULL;
    while((line = get_nth_line(filename, i, NULL))){
        if(strcmp(line, temp) == 0){
            flag = 1;
            free(line);
            break;
        }
        free(line);
        i++;
    }
    if(!flag){
        insert_before_target(filename, temp, INCLUDE_CURSOR);
    }
}
