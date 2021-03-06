#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP "/?"
#define ENCODE "/e"
#define DECODE "/d"
#define CODE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="
#define LEN_B64_CODE 65
#define LAST_CODE_IND (LEN_B64_CODE - 1)
#define ERROR -1
#define MAX_NUM_ORIG_BYTES 3
#define NUM_CONV_BYTES 4
#define EMPTY 0
#define FEW_PAR 1
#define MANY_PAR 2
#define UNKNOWN_PAR 3
#define FILE_NOT_FOUND 4
#define INV_FILE 5
#define FALSE 0
#define TRUE 1

typedef unsigned char uchar;

void help();
void encode(FILE*, FILE*);
int decode(FILE*, FILE*);
void convTo(uchar*, int*, int);
int convFrom(uchar*, uchar*);
int findInd(uchar);
int checkB64File(FILE*);
void convProgress(long, long);
long sizeOfFile(FILE*);
void __exit(int, char*);
int __checkB64File(uchar*);
double countPerDiff(double, double);

#endif /* HEAD_H_INCLUDED */
