#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsList = (SYMBOL**)calloc(MAX_NUM_OF_CHARACTERS, sizeof(SYMBOL));
    unsigned char chr = 0;
    int i = 0;
    int inputFileLenght = countFileLenght(inputFile);

    if(!symbolsList)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    for(i = 0; i < inputFileLenght; i++)
    {
        chr = fgetc(inputFile);

        if(!symbolsList[chr])
        {
            symbolsList[chr] = (SYMBOL*)malloc(sizeof(SYMBOL));

            if(!symbolsList[chr])
            {
                return MEMORY_IS_NOT_ALLOCATED;
            }

            symbolsList[chr]->symbol = chr;
            symbolsList[chr]->frequency = 1;

            continue;
        }

        symbolsList[chr]->frequency += 1;
    }

    for(i = 0; i < MAX_NUM_OF_CHARACTERS; i++)
    {
        if(symbolsList[i])
        {
            fprintf(outputFile, "%c %d\n", symbolsList[i]->symbol, symbolsList[i]->frequency);
        }
    }

    return SUCCESS;
}
