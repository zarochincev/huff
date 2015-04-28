#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsTable = (SYMBOL**)alloc(sizeof(SYMBOL), MAX_NUM_OF_CHARACTERS);
    QUEUE* symbolsList = NULL;

    countSymbolsFrequency(inputFile, symbolsTable);

    symbolsList = createSymbolsList(symbolsTable);

    printSymbolsFrequency(outputFile, symbolsList);

    return SUCCESS;
}

void countSymbolsFrequency(FILE* file, SYMBOL** symbolsTable)
{
    unsigned char chr = 0;
    int fileLenght = countFileLenght(file);
    int i = 0;

    for(i = 0; i < fileLenght; i++)
    {
        chr = fgetc(file);

        if(!symbolsTable[chr])
        {
            symbolsTable[chr] = (SYMBOL*)alloc(sizeof(SYMBOL));
            symbolsTable[chr]->symbol = chr;
            symbolsTable[chr]->frequency = 1;

            continue;
        }

        symbolsTable[chr]->frequency += 1;
    }
}

void printSymbolsFrequency(FILE* file, QUEUE* symbolsList)
{
    while(symbolsList)
    {
        fprintf(file, "%c %d\n", symbolsList->node->symbol->symbol, symbolsList->node->symbol->frequency);

        symbolsList = symbolsList->next;
    }
}

QUEUE* createSymbolsList(SYMBOL** symbolsTable)
{
    int i = 0;
    QUEUE* _queue = NULL;
    QUEUE* head = NULL;
    QUEUE* tmp = NULL;
    QUEUE* prevTmp = NULL;
    size_t nodeSize = sizeof(TREE);
    size_t queueSize = sizeof(QUEUE);

    if(!symbolsTable)
    {
        return NULL;
    }

    for(i = 0; i < MAX_NUM_OF_CHARACTERS; i++)
    {
        if(symbolsTable[i])
        {
            if(!head)
            {
                head = (QUEUE*)alloc(queueSize);
                head->node = (TREE*)alloc(nodeSize);
                head->node->symbol = symbolsTable[i];

                continue;
            }

            _queue = head;
            prevTmp = head;

            while(_queue)
            {
                if(symbolsTable[i]->frequency <= _queue->node->symbol->frequency)
                {
                    tmp = (QUEUE*)alloc(queueSize);
                    tmp->node = (TREE*)alloc(nodeSize);
                    tmp->node->symbol = symbolsTable[i];
                    tmp->next = _queue;

                    if(_queue == head)
                    {
                        head = tmp;
                    }
                }

                _queue = _queue->next;
            }/**< while(_queue) */
        }/**< if(symbolsTable[i]) */
    }/**< for(i = 0; i < MAX_NUM_OF_CHARACTERS; i++) */

    return head;
}
