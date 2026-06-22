#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/node.h"
#include "parse/parseh.h"
#include "parse/strh.h"
#include "common/table.h"


int is_declared_variable(int index){
    return vscan(DEFINED_IDENTIFIER_FILE_NAME, get_token(index)) != -1;
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

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array

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

        // Enqueue left and right children if they exist
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
    }
    return NULL;
}