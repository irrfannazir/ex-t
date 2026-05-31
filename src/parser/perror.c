#include <string.h>
#include "data.h"

int append_error_message(const char *msg){
    //Stack the error messages to be shown.
}

int compare_the_word(char *word, char *token){
    if(!word || !token) return 0;
    return strcmp(word, token) == 0;
}
