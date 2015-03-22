#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define WORD_LENGHT 10
#define WORD_LENGHT_WITH_FINEL_ZERO ((WORD_LENGHT) + (1))
#define KEY_LENGHT 4
#define KEY_LENGHT_WITH_FINEL_ZERO ((KEY_LENGHT) + (1))
#define MAX_HASH_SIZE 10

typedef struct __hash
{
    char* val;
    char* key;
    struct __hash* next;
}HASH;

int hashFunc(char*);
void generateWord(HASH**);
void insertToHash(HASH*, HASH*[]);

#endif /* HEAD_H_INCLUDED*/
