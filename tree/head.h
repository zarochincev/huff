#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __tree
{
    int val;
    struct __tree* right;
    struct __tree* left;
}TREE;

typedef struct __queue
{
    TREE* node;
    struct __queue* next;
}QUEUE;

void createTree(TREE**, TREE*);
void createNode(TREE**, int);
void enqueue(TREE*, QUEUE**);
int dequeue(QUEUE**);
int isEmptyQueue(QUEUE*);
void visitTree(TREE*);

#endif /* HEAD_H_INCLUDED*/
