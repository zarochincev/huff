#include "head.h"

int checkB64File(FILE* file)
{
    int i = 0;
    uchar ch = 0;
    long fSize = sizeOfFile(file);

    if((fSize % 4) != 0)
    {
        return FALSE;
    }

    while(!feof(file))
    {
        checkProgress(ftell(file), fSize);
        fread(&ch, sizeof(uchar), 1, file);

        i = 0;

        while(i < LEN_B64_CODE)
        {
            if(ch == CODE[i])
            {
                break;
            }
            i++;
        }

        if(i == LEN_B64_CODE)
        {
            return FALSE;
        }
    }
    rewind(file);

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

void checkProgress(long cur, long size)
{
    double diff = 0;
    static int perDiff = 0;

    diff = ((double)cur / (double)size) * 100;

    if(perDiff < (int)diff)
    {
        perDiff = diff;
        printf("Checking: %d\%\r", perDiff);
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

    case F_NOT_FOUND:
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
