#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsTable = (SYMBOL**)calloc(MAX_NUM_OF_CHARACTERS, sizeof(SYMBOL));
    int error = 0;
    QUEUE* symbolsList = NULL;

    if(!symbolsTable)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    error = countSymbolsFrequency(inputFile, symbolsTable);

    if(error)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    symbolsList = createSymbolsList(symbolsTable);

    if(!symbolsList)
    {
        return MEMORY_IS_NOT_ALLOCATED;
    }

    printSymbolsFrequency(outputFile, symbolsList);

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
                head = (QUEUE*)malloc(queueSize);

                if(!head)
                {
                    return NULL;
                }

                memset(head, 0, queueSize);

                head->node = (TREE*)malloc(nodeSize);

                if(!head->node)
                {
                    return NULL;
                }

                memset(head->node, 0, nodeSize);

                head->node->symbol = symbolsTable[i];
            }

            _queue = head;

            while(_queue)
            {
                if(symbolsTable[i]->frequency <= _queue->node->symbol->frequency)
                {
                    tmp = (QUEUE*)malloc(queueSize);

                    if(!tmp)
                    {
                        return NULL;
                    }

                    memset(tmp, 0, queueSize);

                    tmp->node = (TREE*)malloc(nodeSize);

                    if(!tmp->node)
                    {
                        return NULL;
                    }

                    memset(tmp->node, 0, nodeSize);

                    tmp->node->symbol = symbolsTable[i];
                    tmp->next = _queue;

                    if(_queue == head)
                    {
                        head = tmp;
                    }
                }

                _queue = _queue->next;
            }
        }
    }

    return head;
}
