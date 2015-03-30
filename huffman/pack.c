#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsTable = (SYMBOL**)calloc(MAX_NUM_OF_CHARACTERS, sizeof(SYMBOL));
    int error = 0;

    if(!symbolsTable)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    error = countSymbolsFrequency(inputFile, symbolsTable);

    if(error)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    printSymbolsFrequency(outputFile, symbolsTable);

    return SUCCESS;
}

int countSymbolsFrequency(FILE* file, SYMBOL** symbolsTable)
{
    unsigned char chr = 0;
    int fileLenght = countFileLenght(file);
    int i = 0;

    for(i = 0; i < fileLenght; i++)
    {
        chr = fgetc(file);

        if(!symbolsTable[chr])
        {
            symbolsTable[chr] = (SYMBOL*)malloc(sizeof(SYMBOL));

            if(!symbolsTable[chr])
            {
                return MEMORY_IS_NOT_ALLOCATED;
            }

            symbolsTable[chr]->symbol = chr;
            symbolsTable[chr]->frequency = 1;

            continue;
        }

        symbolsTable[chr]->frequency += 1;
    }

    return SUCCESS;
}

void printSymbolsFrequency(FILE* file, SYMBOL** symbolsTable)
{
    int i = 0;

    for(i = 0; i < MAX_NUM_OF_CHARACTERS; i++)
    {
        if(symbolsTable[i])
        {
            fprintf(file, "%c %d\n", symbolsTable[i]->symbol, symbolsTable[i]->frequency);
        }
    }
}
