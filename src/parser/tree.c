#include <stdio.h>
#include <stdlib.h>
#include "parse/tree.h"
#include "data.h"
#include "parse/pdebug.h"

#ifdef DISPLAY_TREE
    void displayTree(struct Node *root) {
        if (root == NULL) {
            return;
        }
        
        if(root -> left == NULL && root -> right == NULL){
            for(int i = root -> start ; i < root -> start + root -> size; i++){
                char *token = get_token(i);
                printf("%s ", token ? token : "");
                free(token);
            }
            // printf("\n");
        }
        displayTree(root->right);
        displayTree(root->left);
    }
#endif

/*It is the where parsing tree in implemented*/
int parsing_tree_analysis(char *format, int start, int size){
    struct Node *root = createNode(format, EXPRESSION, start, size);
    struct Node *ptr = find_next_expression(root);
    int endloop = 0;
    while(ptr != NULL && endloop < 20){
        #ifdef P_TREE_MODE
         char *start_token = get_token(ptr -> start);
         char *end_token = get_token(ptr -> start + ptr -> size);
         printf("from %s", start_token ? start_token : "");
         printf("to %s\n", end_token ? end_token : "");
         free(start_token);
         free(end_token);
        #endif
        int status = analyze_expression(ptr);
        #ifdef DISPLAY_TREE
            displayTree(root); 
            printf("\n\n");
        #endif
        if(status){
            printf("Invalid Expression.\n");
            return 1;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    return 0;
}
