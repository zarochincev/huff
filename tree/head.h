#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct __tree
{
    int val;
    struct __tree* right;
    struct __tree* left;
}TREE;

void createTree(TREE**, TREE*);
void printTree(TREE*);
void createNode(TREE**, int);

#endif /* HEAD_H_INCLUDED*/
