#include "head.h"

double countPerDiff(double first, double second)
{
    return ((first / second) * 100);
}

long sizeOfFile(FILE* file)
{
    long fSize = 0L;

    fseek(file, 0, SEEK_END);

    fSize = ftell(file);

    rewind(file);

    return fSize;
}

void convProgress(long cur, long size)
{
    double diff = 0;
    static int perDiff = 0;

    diff = countPerDiff((double)cur, (double)size);

    if(perDiff < (int)diff)
    {
        perDiff = diff;
        printf("Progress: %d%\r", perDiff);
    }

    return;
}
