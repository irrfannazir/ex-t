#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/node.h"
#include "parse/strh.h"
#include "common/table.h"
#include "data.h"

int is_declared_variable(int index){
    char *token = get_token(index);
    int declared = token && vscan(DEFINED_IDENTIFIER_FILE_NAME, token) != -1;
    free(token);
    return declared;
}

int is_unidentified(struct Node *ptr){
    if(ptr -> size > 1){
        return 1;
    }
    else if(ptr -> size == 1){
        if(get_type(ptr -> start) == TOKEN_INTEGER){
            return 0;
        }else if(get_type(ptr -> start) == TOKEN_IDENTIFIER && is_declared_variable(ptr -> start)){
            return 0;
        }else if(get_type(ptr -> start) == TOKEN_STRING){
            return 0;
        }
        return 1;
    }
    return ptr -> size != 1;
}

struct Node *find_next_expression(struct Node* root) {
    int index = 0;
    if ( !root ) return NULL;
    if (root -> data == 0 && root -> size > 1 && root -> right == NULL && root -> left == NULL) return root;

    
    struct Node* queue[100];  
    int front = 0, rear = 0;

    
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];

        

        if(
            current -> data == EXPRESSION
                &&
            is_unidentified(current)
                &&
            current -> right == NULL
                &&
            current -> left == NULL
        ){
            return current;
        }
        (index)++;

        
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
    }
    return NULL;
}
