#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char *error = NULL;
int error_priority = 0;
int current_error_priority = 0;

void push_error(const char *temp){
    if(error_priority > current_error_priority){
        current_error_priority = error_priority;
    }else{
        return;
    }
    if( error ){
        free(error);
    }
    error = malloc( (strlen(temp) + 1)*sizeof(char) );
    if(error == NULL){
        perror("Allocation failed for error.\n");
    }
    strcpy(error, temp);
}

void print_error(){
    if( error ){
        printf("%s\n", error);
        free(error);
        error_priority = 0;
        current_error_priority = 0;
    }
    error = NULL;
}
