#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCORRECT_FILE 1
#define MEMORY_IS_NOT_ALLOCATED 2
#define MAX_HASH_SIZE 3

typedef struct __hash
{
    int key;
    char* val;
    struct __hash* next;
}HASH;

void __exit(int, char*);
void insertToHashTable(HASH*, HASH**);
int hashFunc(int);

#endif /* HEAD_H_INCLUDED*/
