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

typedef struct SYM
{
    char symbol;
    int number;
    struct SYM* next;
}SYMBOL;

void pack(FILE*, FILE*);
SYMBOL* countSym(FILE*);
void sortList(SYMBOL*);
void help();

#endif /* HEAD_H_INCLUDED*/
