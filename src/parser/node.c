#include "parse/tree.h"
#include <stdlib.h>
#include <stdio.h>

void *createNode(char *value, int data, int start, int size){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->format = value;
    newNode->data = data;
    newNode->start = start;
    newNode->size = size;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

