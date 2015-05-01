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

    return;
}

void printSymbolsFrequency(FILE* file, QUEUE* symbolsList)
{
    while(symbolsList)
    {
        fprintf(file, "%c%d ", queueMemberSymbol(symbolsList), queueMemberFreq(symbolsList));

        symbolsList = symbolsList->next;
    }

    fprintf(file, "\n");

    return;
}

QUEUE* createSymbolsList(SYMBOL** symbolsTable)
{
    int i = 0;
    QUEUE* _queue = NULL;
    QUEUE* head = NULL;
    QUEUE* tmp = NULL;
    QUEUE* prevQueue = NULL;

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
                head = createQueueMember(symbolsTable[i]);

                continue;
            }

            _queue = head;

            while(_queue)
            {
                if(symbolsTable[i]->frequency < queueMemberFreq(_queue))
                {
                    if(_queue == head)
                    {
                        tmp = createQueueMember(symbolsTable[i]);
                        tmp->next = head;
                        head = tmp;
                        _queue = head;

                        break;
                    }else/**< if(_queue == head) */
                    {
                        tmp = createQueueMember(symbolsTable[i]);
                        prevQueue->next = tmp;
                        tmp->next = _queue;
                        _queue = head;

                        break;
                    }
                }else if(symbolsTable[i]->frequency == queueMemberFreq(_queue))/**< if(symbolsTable[i]->frequency < _queue->node->symbol->frequency) */
                {
                    if(symbolsTable[i]->symbol < queueMemberSymbol(_queue))
                    {
                        if(_queue == head)
                        {
                            tmp = createQueueMember(symbolsTable[i]);
                            tmp->next = head;
                            head = tmp;
                            _queue = head;

                            break;
                        }else/**< if(_queue == head) */
                        {
                            tmp = createQueueMember(symbolsTable[i]);
                            prevQueue->next = tmp;
                            tmp->next = _queue;
                            _queue = head;

                            break;
                        }
                    }else/**< if(symbolsTable[i]->symbol < _queue->node->symbol->symbol) */
                    {
                        if(!_queue->next)
                        {
                            tmp = createQueueMember(symbolsTable[i]);
                            _queue->next = tmp;
                            _queue = head;

                            break;
                        }else/**< if(!_queue->next) */
                        {
                            _queue = _queue->next;

                            continue;
                        }
                    }
                }else/**< if(symbolsTable[i]->frequency < _queue->node->symbol->frequency) */
                {
                    if(!_queue->next)
                    {
                        tmp = createQueueMember(symbolsTable[i]);
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
    {
        firstChildQueue = dequeue(&head);
        secondChildQueue = dequeue(&head);
        firstChild = firstChildQueue->node;
        secondChild = secondChildQueue->node;

        parent = (TREE*)alloc(sizeOfNode, 1);
        parent->symbol = (SYMBOL*)alloc(sizeOfSymbol, 1);
        parent->left = firstChild;
        parent->right = secondChild;
        parent->symbol->frequency = treeNodeFreq(firstChild) + treeNodeFreq(secondChild);

        enqueue(parent, &head);
    }

    root = head->node;

    return root;
}

void printTree(FILE* file, TREE* root)
{
    fprintf(file, "%c%d ", treeNodeSymbol(root), treeNodeFreq(root));

    if(root->left)
    {
        printTree(file, root->left);
    }

    if(root->right)
    {
        printTree(file, root->right);
    }

    return;
}
