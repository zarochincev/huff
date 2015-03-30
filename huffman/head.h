#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SUCCESS 0
#define ONLY_PROGRAMM_NAME 1
#define TOO_FEW_PARAMETERS 1
#define UNKNOWN_PARAMETER 2
#define TOO_MANY_PARAMETERS 3
#define INVALID_FILE 4
#define MEMORY_IS_NOT_ALLOCATED 5
#define ONE_PARAMETER 2
#define TWO_PARAMETERS 3
#define TREE_PARAMETERS 4
#define PARAMETER '-'
#define HELP '?'
#define ARCHIVE 'a'
#define EXTRACT 'e'
#define MAX_FILE_NAME_LENGHT 256
#define MAX_NUM_OF_CHARACTERS ((UCHAR_MAX) + (1))

typedef struct __symbol
{
    unsigned char symbol;
    int frequency;
}SYMBOL;

typedef struct __tree
{
    SYMBOL* symbol;
    struct __tree* left;
    struct __tree* right;
}TREE;

typedef struct __queue
{
    TREE* node;
    struct __queue* next;
}QUEUE;

void __exit(int, char*);
void help();
int pack(FILE*, FILE*);
void extract();
char* createFileName(char*);
int countFileLenght(FILE*);
int countSymbolsFrequency(FILE*, SYMBOL**);
void printSymbolsFrequency(FILE*, QUEUE*);
QUEUE* createSymbolsList(SYMBOL**);

#endif /*HEAD_H_INCLUDED*/
