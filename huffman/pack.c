#include "head.h"

int pack(FILE* inputFile, FILE* outputFile)
{
    SYMBOL** symbolsTable = (SYMBOL**)alloc(sizeof(SYMBOL), MAX_NUM_OF_CHARACTERS);
    QUEUE* symbolsList = NULL;
    TREE* tree = NULL;
    unsigned char byte = 0;
    unsigned char buffer = 0;
    int i = 0;
    int codeLenghtCounter = 0;

    countSymbolsFrequency(inputFile, symbolsTable);

    symbolsList = createSymbolsList(symbolsTable);

    printSymbolsFrequency(outputFile, symbolsList);
    fprintf(outputFile, "\n");

    tree = createTree(symbolsList);

    printTree(outputFile, tree);
    fprintf(outputFile, "\n");

    createSymbolsCode(tree, NULL);

    printSymbolsCode(outputFile, tree);
    fprintf(outputFile, "\n");

    rewind(inputFile);

    while(!feof(inputFile))
    {
        fread(&byte, 1, 1, inputFile);

        for(codeLenghtCounter = 0; codeLenghtCounter < strlen(symbolsTable[byte]->code); codeLenghtCounter++)
        {
            if(symbolsTable[byte]->code[codeLenghtCounter] == '1')
            {
                buffer |= 1;
                buffer <<= 1;
                i++;
            }else if(symbolsTable[byte]->code[codeLenghtCounter] == '0')
            {
                buffer <<= 1;
                i++;
            }

            if(i == 7)
            {
                fwrite(&buffer, 1, 1, outputFile);
                buffer = 0;
                i = 0;
            }
        }
    }

    fwrite(&buffer, 1, 1, outputFile);

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
                    }else
                    {
                        tmp = createQueueMember(symbolsTable[i]);
                        prevQueue->next = tmp;
                        tmp->next = _queue;
                        _queue = head;

                        break;
                    }
                }else if(symbolsTable[i]->frequency == queueMemberFreq(_queue))/**< if(symbolsTable[i]->frequency < queueMemberFreq(_queue)) */
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
                        }else
                        {
                            tmp = createQueueMember(symbolsTable[i]);
                            prevQueue->next = tmp;
                            tmp->next = _queue;
                            _queue = head;

                            break;
                        }
                    }else/**< if(symbolsTable[i]->symbol < queueMemberSymbol(_queue)) */
                    {
                        if(!_queue->next)
                        {
                            tmp = createQueueMember(symbolsTable[i]);
                            _queue->next = tmp;
                            _queue = head;

                            break;
                        }else
                        {
                            prevQueue = _queue;
                            _queue = _queue->next;

                            continue;
                        }
                    }/**< if(symbolsTable[i]->symbol < queueMemberSymbol(_queue)) */
                }else/**< if(symbolsTable[i]->frequency < queueMemberFreq(_queue))) */
                {
                    if(!_queue->next)
                    {
                        tmp = createQueueMember(symbolsTable[i]);
                        _queue->next = tmp;
                        _queue = head;

                        break;
                    }
                }/**< if(symbolsTable[i]->frequency < queueMemberFreq(_queue)) */

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

void createSymbolsCode(TREE* root, char* code)
{
    static int i = 0;

    if(!code)
    {
        code = (char*)alloc(sizeof(char), MAX_NUM_OF_CHARACTERS);
    }

    if(root->left)
    {
        code[i] = '0';
        i++;
        createSymbolsCode(root->left, code);
    }

    if(root->right)
    {
        code[i] = '1';
        i++;
        createSymbolsCode(root->right, code);
    }

    if(root->symbol->symbol)
    {
        root->symbol->code = (char*)alloc(sizeof(char), strlen(code));
        strcpy(root->symbol->code, code);
        code[i] = 0;
        i--;
    }
}
