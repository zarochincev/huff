#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONLY_PROGRAMM_NAME 1
#define TOO_FEW_PARAMETERS 1
#define UNKNOWN_PARAMETER 2
#define TOO_MANY_PARAMETERS 3
#define INVALID_FILE 4
#define ONE_PARAMETER 2
#define TWO_PARAMETERS 3
#define TREE_PARAMETERS 4
#define PARAMETER '-'
#define HELP '?'
#define ARCHIVE 'a'
#define EXTRACT 'e'
#define MAX_FILE_NAME_LENGHT 256

typedef struct __symbol
{
    unsigned char symbol;
    unsigned int frequency;
}SYMBOL;

void __exit(int, char*);
void help();
void pack(FILE*, FILE*);
void extract(FILE*, FILE*);
char* createFileName(char*);

#endif /*HEAD_H_INCLUDED*/
