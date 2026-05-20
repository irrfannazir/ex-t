#ifndef TREE_CONSTANTS_H
#define TREE_CONSTANTS_H
#include "node.h"

extern int ssn;

void *createNode(char *value, int data, int start, int size);
struct Node *find_next_expression(struct Node* root);
int analyze_expression(struct Node *root);

#endif