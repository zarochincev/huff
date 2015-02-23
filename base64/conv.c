#include "head.h"

void encode(FILE* inFile, FILE* outFile)
{
    int numReadedByte = 0;
    int i = 0;
    uchar* origByte = (uchar*)malloc(sizeof(uchar) * MAX_NUM_ORIG_BYTES);
    int* convByteInd = (int*)malloc(sizeof(int) * NUM_CONV_BYTES);
    long inFileSize = sizeOfFile(inFile);

    do
    {
        convProgress(ftell(inFile), inFileSize);

        numReadedByte = fread(origByte, 1, MAX_NUM_ORIG_BYTES, inFile);

        if(!numReadedByte)
        {
            break;
        }

        convTo(origByte, convByteInd, numReadedByte);

        for(i = 0; i < NUM_CONV_BYTES; i++)
        {
            fwrite(&CODE[convByteInd[i]], 1, 1, outFile);
        }

    }while(numReadedByte);

    free(origByte);
    free(convByteInd);
}

int decode(FILE* inFile, FILE* outFile)
{
    uchar* convByte = (uchar*)malloc(sizeof(uchar) * NUM_CONV_BYTES);
    uchar* origByte = (uchar*)malloc(sizeof(uchar) * MAX_NUM_ORIG_BYTES);
    int numOrigByte = 0;
    long inFileSize = sizeOfFile(inFile);

    do
    {
        convProgress(ftell(inFile), inFileSize);
        memset(convByte, EMPTY, NUM_CONV_BYTES);

        if(!fread(convByte, NUM_CONV_BYTES, 1, inFile))
        {
            break;
        }

        if(!__checkB64File(convByte))
        {
            return FALSE;
        }


        numOrigByte = convFrom(convByte, origByte);

        fwrite(origByte, numOrigByte, 1, outFile);

    }while(numOrigByte);

    free(convByte);
    free(origByte);

    return TRUE;
}

void convTo(uchar* origByte, int* convByteInd, int numByte)
{
    switch(numByte)
    {
    case 0:

        return;

    case 1:
        convByteInd[0] = origByte[0] >> 2;
        convByteInd[1] = (origByte[0] & 0x3) << 4;
        convByteInd[2] = LAST_CODE_IND;
        convByteInd[3] = LAST_CODE_IND;

        return;

    case 2:
        convByteInd[0] = origByte[0] >> 2;
        convByteInd[1] = (origByte[0] & 0x3) << 4;
        convByteInd[1] = convByteInd[1] | (origByte[1] >> 4);
        convByteInd[2] = (origByte[1] & 0xf) << 2;
        convByteInd[3] = LAST_CODE_IND;

        return;

    default:
        convByteInd[0] = origByte[0] >> 2;
        convByteInd[1] = (origByte[0] & 0x3) << 4;
        convByteInd[1] = convByteInd[1] | (origByte[1] >> 4);
        convByteInd[2] = (origByte[1] & 0xf) << 2;
        convByteInd[2] = convByteInd[2] | (origByte[2] >> 6);
        convByteInd[3] = origByte[2] & 0x3f;

        return;
    }
}

int convFrom(uchar* convByte, uchar* origByte)
{
    int* convByteInd = (int*)malloc(sizeof(int) * NUM_CONV_BYTES);
    int i = 0;

    for(i = 0; i < NUM_CONV_BYTES; i++)
    {
        convByteInd[i] = findInd(convByte[i]);

        if(convByteInd[i] == ERROR)
        {
            return 0;
        }
    }

    origByte[0] = (convByteInd[0] << 2) | (convByteInd[1] >> 4);

    if(convByteInd[2] != LAST_CODE_IND)
    {
        origByte[1] = (convByteInd[1] << 4) | (convByteInd[2] >> 2);
    }else
    {
        return 1;
    }

    if(convByteInd[3] != LAST_CODE_IND)
    {
        origByte[2] = (convByteInd[2] << 6) | convByteInd[3];
    }else
    {
        return 2;
    }

    free(convByteInd);

    return 3;
}

int findInd(uchar byte)
{
    int i = 0;

    for(i = 0; i < LEN_B64_CODE; i++)
    {
        if(byte == CODE[i])
        {
            return i;
        }
    }

    return ERROR;
}
