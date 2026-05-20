#include <string.h>
#include "data.h"

const char *find_datatype(int index){
    if(strcmp(get_token(index), "single") == 0){
        return "int";
    }
    return NULL;
}