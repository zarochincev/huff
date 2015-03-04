#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1;
#define HELP '?'
#define ADD 'a'
#define EXTRACT 'x'
#define PARAMETER '/'
#define EMPTY 0
#define DEBUG "/d"

typedef struct __symbol
{
    unsigned char symbol;
    unsigned int freq;
    struct __symbol* next;
}SYMBOL;

typedef struct __tree
{
    struct __tree* left;
    struct __tree* right;
    int code;
    SYMBOL* symbol;
}TREE;

typedef struct __queue
{
    TREE* node;
    struct __queue* next;
}QUEUE;

void pack(FILE*, FILE*);
SYMBOL* countSymFreq(FILE*);
void sortList(SYMBOL*);
void help();
void writeSymbolFreq(SYMBOL*, FILE*);
void enqueue(QUEUE*, QUEUE*);
TREE* createTree(QUEUE*);
QUEUE* dequeue(QUEUE**);
QUEUE* createQueue(SYMBOL*);
unsigned int getFreq(QUEUE*);

#endif /* HEAD_H_INCLUDED*/
