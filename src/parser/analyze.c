#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/tree.h"
#include "parse/syntax.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "data.h"

int compare_the_word(char *word, char *token);
int does_tree_needed(char *word); //Is word contains and ending with ':'

static inline int count_tree_needed_words(char *line){
    int count = 0;
    char *copy = strdup(line);
    if (!copy) return 0;
    
    char *token = strtok(copy, " \t\n");
    while(token != NULL){
        if(does_tree_needed(token)){
            count++;
        }
        token = strtok(NULL, " \t\n");
    }    
    free(copy);
    return count;
}

static inline int handle_tertiary_op(struct Node *ptr, char *word, int ci) {
    if (ptr->right != NULL) {
        ptr->right->right = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
        ptr->right->left = createNode(NULL, EXPRESSION, ci + 1, -1);
    } else {
        ptr->left = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
        ptr->right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
        ci--;
    }
    return ci;
}

static inline void handle_binary_op(struct Node *ptr, char *word, int ci) {
    if(ptr -> left && ptr->right->left->format == NULL){
        // assign the endpoint of the binary production rule
        const int start = ptr->right->left->start;
        const int size = ptr->right->left->size;
        const int decr = start + size - ci;
        ptr->right->left->format = strdup(word);
        ptr->right->left->size = size - decr;
        return;
    }
    ptr->left = createNode(NULL, OPERATOR, ci, 1);
    ptr->right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
    ptr->right->right = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
    ptr->right->left = createNode(NULL, EXPRESSION, ci + 1,
        (ptr->start + ptr->size) - (ci + 1)); 
}

static inline void assign_last_word(struct Node *ptr, char *word, int nos) {
    if (ptr->right && ptr->right->right) {
        if (nos == 3) {
            ptr->right->left->format = strdup(word);
            ptr->right->left->size =
                (ptr->start + ptr->size) - ptr->right->left->start;
        } else if (nos == 2) {
            ptr->right->left->format = strdup(word);
            ptr->right->left->size =
                (ptr->start + ptr->size) - ptr->right->left->start;
        }
    }    
    if (nos == 1){
        free(ptr->format);
        ptr -> format = strdup(word);
    }
}

static inline int find_matching_token(int ci, char *end) {
    while (
        get_token(ci) != NULL &&
        !compare_the_word(end, get_token(ci))
    ) {
        ci++;
    }
    return ci;
}

static inline int check_line(struct Node *ptr, char *syn_line) {
    int nos = count_tree_needed_words(syn_line);
    int ci = ptr->start;
    
    char *copy = strdup(syn_line);
    if (!copy) return 1;
    
    char *word = strtok(copy, " \t\n");

    while (word != NULL) {
        if (does_tree_needed(word)) {
            char *end = strtok(NULL, " \t\n");

            if (end != NULL) {
                ci = find_matching_token(ci, end);
                
                if (ci == ptr->start + ptr->size) {
                    free(copy);
                    return 1;
                }
                
                switch (nos) {
                    case 3:
                        ci = handle_tertiary_op(ptr, word, ci);
                        break;
                    case 2:
                        handle_binary_op(ptr, word, ci);
                        break;
                }
            } else {
                assign_last_word(ptr, word, nos);
                free(copy);
                return 0;
            }
        } 
        else if (!compare_the_word(word, get_token(ci))) {
            free(copy);
            return 1;
        }

        word = strtok(NULL, " \t\n");
        ci++;
    }
    if(ptr -> left == NULL && ptr -> right == NULL) ptr -> data = TERMINAL;
    free(copy);
    return 0;
}

int analyze_expression(struct Node *ptr){
    if(ptr -> format == NULL) return 1;
    
    // Go through each line from syntax.txt
    int ln = 0;
    char *syn_line = get_nth_line(SYNTAX_DIRECTORY, ln, ptr -> format);
    
    ln++;
    while(syn_line != NULL){
        if(syn_line[0] == '\n'){
            free(syn_line);
            return 1;
        }
        const int status = check_line(ptr, syn_line);
        if(status){
            syn_line = get_nth_line(SYNTAX_DIRECTORY, ln, ptr -> format);
            ln++;
        }else{
            free(syn_line);
            return 0;
        }
    }
    free(syn_line);
    return 1;
}
