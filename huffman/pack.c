#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsTable = (SYMBOL**)alloc(sizeof(SYMBOL), MAX_NUM_OF_CHARACTERS);
    QUEUE* symbolsList = NULL;
    TREE* tree = NULL;

    countSymbolsFrequency(inputFile, symbolsTable);

    symbolsList = createSymbolsList(symbolsTable);

    printSymbolsFrequency(outputFile, symbolsList);

    tree = createTree(symbolsList);

    printTree(outputFile, tree);

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
            symbolsTable[chr] = (SYMBOL*)alloc(sizeof(SYMBOL), 1);
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
        fprintf(file, "%c%d ", symbolsList->node->symbol->symbol, symbolsList->node->symbol->frequency);

        symbolsList = symbolsList->next;
    }

    fprintf(file, "\n");
}

QUEUE* createSymbolsList(SYMBOL** symbolsTable)
{
    int i = 0;
    QUEUE* _queue = NULL;
    QUEUE* head = NULL;
    QUEUE* tmp = NULL;
    QUEUE* prevQueue = NULL;
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
                head = (QUEUE*)alloc(queueSize, 1);
                head->node = (TREE*)alloc(nodeSize, 1);
                head->node->symbol = symbolsTable[i];

                continue;
            }

            _queue = head;

            while(_queue)
            {
                if(symbolsTable[i]->frequency <= _queue->node->symbol->frequency)
                {
                    if(_queue == head)
                    {
                        tmp = (QUEUE*)alloc(queueSize, 1);
                        tmp->node = (TREE*)alloc(nodeSize, 1);
                        tmp->node->symbol = symbolsTable[i];
                        tmp->next = head;
                        head = tmp;
                        _queue = head;

                        break;
                    }else
                    {
                        tmp = (QUEUE*)alloc(queueSize, 1);
                        tmp->node = (TREE*)alloc(nodeSize, 1);
                        tmp->node->symbol = symbolsTable[i];
                        prevQueue->next = tmp;
                        tmp->next = _queue;
                        _queue = head;

                        break;
                    }
                }else/**< if(symbolsTable[i]) */
                {
                    if(!_queue->next)
                    {
                        tmp = (QUEUE*)alloc(queueSize, 1);
                        tmp->node = (TREE*)alloc(nodeSize, 1);
                        tmp->node->symbol = symbolsTable[i];
                        _queue->next = tmp;
                        _queue = head;

                        break;
                    }
                }

                prevQueue = _queue;
                _queue = _queue->next;
            }/**< while(_queue) */
        }/**< if(symbolsTable[i]) */
    }/**< for(i = 0; i < MAX_NUM_OF_CHARACTERS; i++) */

    return head;
}

TREE* createTree(QUEUE* head)
{
    TREE* root = NULL;
    TREE* firstChild = NULL;
    TREE* secondChild = NULL;
    TREE* parent = NULL;
    QUEUE* firstChildQueue = NULL;
    QUEUE* secondChildQueue = NULL;
    size_t sizeOfNode = sizeof(TREE);
    size_t sizeOfSymbol = sizeof(SYMBOL);

    while(head->next)
    {printSymbolsFrequency(stdout, head);
        firstChildQueue = dequeue(&head);
        secondChildQueue = dequeue(&head);
        firstChild = firstChildQueue->node;
        secondChild = secondChildQueue->node;

        parent = (TREE*)alloc(sizeOfNode, 1);
        parent->symbol = (SYMBOL*)alloc(sizeOfSymbol, 1);
        parent->left = firstChild;
        parent->right = secondChild;
        parent->symbol->frequency = firstChild->symbol->frequency + secondChild->symbol->frequency;

        enqueue(parent, &head);
    }
printSymbolsFrequency(stdout, head);
    root = head->node;

    return root;
}

void printTree(FILE* file, TREE* root)
{
    fprintf(file, "%c%d ", root->symbol->symbol, root->symbol->frequency);

    if(root->left)
    {
        printTree(file, root->left);
    }

    if(root->right)
    {
        printTree(file, root->right);
    }

}
