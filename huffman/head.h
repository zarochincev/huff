#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS /**< kill visual studio secure warnings */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>

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

enum ERRORS
{
    SUCCESS = 0,
    ONLY_PROGRAMM_NAME = 1,
    TOO_FEW_PARAMETERS = 1,
    UNKNOWN_PARAMETER = 2,
    TOO_MANY_PARAMETERS = 3,
    INVALID_FILE = 4,
    MEMORY_IS_NOT_ALLOCATED = 5
};

enum PARAMETERS
{
    PARAMETER = '-',
    HELP = '?',
    ARCHIVE = 'a',
    EXTRACT = 'e'
};

enum NUM_OF_PARAMETERS
{
    ONE_PARAMETER = 2,
    TWO_PARAMETERS = 3,
    TREE_PARAMETERS = 4
};

void __exit(int, ...);
void help();
int pack(FILE*, FILE*);
void extract();
char* createFileName(char*);
int countFileLenght(FILE*);
void countSymbolsFrequency(FILE*, SYMBOL**);
void printSymbolsFrequency(FILE*, QUEUE*);
QUEUE* createSymbolsList(SYMBOL**);
void* alloc(size_t, size_t);

#endif /*HEAD_H_INCLUDED*/
