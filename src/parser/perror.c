#include <string.h>
#include "data.h"

int compare_the_word(char *word, char *token){
    if(!word || !token) return 0;
    return strcmp(word, token) == 0;
}
