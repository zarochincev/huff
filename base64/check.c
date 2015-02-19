#include "head.h"

int checkB64File(FILE* file)
{
    long fSize = sizeOfFile(file);

    if((fSize % NUM_CONV_BYTES) != 0)
    {
        return FALSE;
    }

    return TRUE;
}

void convProgress(long cur, long size)
{
    double diff = 0;
    static int perDiff = 0;

    diff = ((double)cur / (double)size) * 100;

    if(perDiff < (int)diff)
    {
        perDiff = diff;
        printf("Progress: %d\%\r", perDiff);
    }

    return;
}

long sizeOfFile(FILE* file)
{
    long fSize = 0L;

    fseek(file, 0, SEEK_END);

    fSize = ftell(file);

    rewind(file);

    return fSize;
}


void __exit(int err, char* arg)
{
    switch(err)
    {
    case FEW_PAR:
        puts("ERROR : Too few parameters\n");
        exit(0);

        break;

    case MANY_PAR:
        puts("ERROR : Too many parameters\n");
        exit(0);

        break;

    case UNKNOWN_PAR:
        printf("ERROR : Unknown parameter %s\n", arg);
        exit(0);

        break;

    case FILE_NOT_FOUND:
        printf("ERROR : File %s not found\n", arg);
        exit(0);

        break;

    case INV_FILE:
        printf("ERROR : %s not BASE64 file\n", arg);
        exit(0);

        break;
    }

    return;
}

void __checkB64File(uchar* ch)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < NUM_CONV_BYTES; i++)
    {
        while(j < LEN_B64_CODE)
        {
            if(ch[i] == CODE[i])
            {
                break;
            }
            j++;
        }

        if(j == LEN_B64_CODE)
        {
            __exit(INV_FILE, NULL);
        }
    }
    return;
}
