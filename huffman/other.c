#include "head.h"

void __exit(int errorCode, ...)
{
    va_list argList = NULL;

    va_start(argList, errorCode);

    switch(errorCode)
    {
    case SUCCESS:
        puts("Successfully");
        break;

    case TOO_FEW_PARAMETERS:
        puts("ERROR : Too few parameters\nUse \"-?\" for help");
        break;

    case UNKNOWN_PARAMETER:
        printf("ERROR : Unknown parameter %s\nUse \"-?\" for help", va_arg(argList, char*));
        break;

    case TOO_MANY_PARAMETERS:
        puts("ERROR : Too many parameters\nUse \"-?\" for help");
        break;

    case INVALID_FILE:
        printf("ERROR : %s invalid file", va_arg(argList, char*));
        break;

    case MEMORY_IS_NOT_ALLOCATED:
        puts("ERROR : Not enough memory");
        break;
    }

    va_end(argList);

    exit(errorCode);
}

void help()
{
    puts("Help will be here");
    exit(0);
}

char* createFileName(char* image)
{
    char* name = (char*)calloc(MAX_FILE_NAME_LENGHT, sizeof(char));

    name = strcpy(name, "huff.");
    name = strcat(name, image);

    return name;
}

int countFileLenght(FILE* file)
{
    int lenght = 0;

    fseek(file, 0, SEEK_END);
    lenght = ftell(file);
    rewind(file);

    return lenght;
}

void* alloc(size_t size, size_t num)
{
    void* tmp = NULL;

    if(num != 1)
    {
        tmp = calloc(num, size);

        if(!tmp)
        {
            __exit(MEMORY_IS_NOT_ALLOCATED);
        }
    }else
    {
        tmp = malloc(size);

        if(!tmp)
        {
            __exit(MEMORY_IS_NOT_ALLOCATED);
        }

        memset(tmp, 0, size);
    }

    return tmp;
}

QUEUE* dequeue(QUEUE** head)
{
    QUEUE* tmp = NULL;

    tmp = *head;
    *head = (*head)->next;

    return tmp;
}

void enqueue(TREE* node, QUEUE** head)
{
    QUEUE* tmp = (QUEUE*)alloc(sizeof(QUEUE), 1);
    QUEUE* _queue = NULL;
    QUEUE* prevQueue = NULL;

    if(!(*head))
    {
        tmp->node = node;
        (*head) = tmp;

        return;
    }

    _queue = (*head);

    while(_queue)
    {
        if(treeNodeFreq(node) <= queueMemberFreq(_queue))
        {
            if(_queue == *head)
            {
                tmp->node = node;
                tmp->next = *head;
                *head = tmp;
                _queue = *head;

                break;
            }else
            {
                tmp->node = node;
                prevQueue->next = tmp;
                tmp->next = _queue;
                _queue = *head;

                break;
            }
        }else/**< if(treeNodeFreq(node) <= queueMemberFreq(_queue)) */
        {
            if(!_queue->next)
            {
                tmp->node = node;
                _queue->next = tmp;
                _queue = *head;

                break;
            }
        }/**< if(treeNodeFreq(node) <= queueMemberFreq(_queue)) */

        prevQueue = _queue;
        _queue = _queue->next;
    }/**< while(_queue) */

    return;
}

QUEUE* createQueueMember(SYMBOL* symbol)
{
    QUEUE* tmp = (QUEUE*)alloc(sizeof(QUEUE), 1);

    tmp->node = (TREE*)alloc(sizeof(TREE), 1);
    tmp->node->symbol = symbol;

    return tmp;
}

int queueMemberFreq(QUEUE* member)
{
    return member->node->symbol->frequency;
}

int treeNodeFreq(TREE* node)
{
    return node->symbol->frequency;
}

unsigned char queueMemberSymbol(QUEUE* member)
{
    return member->node->symbol->symbol;
}

unsigned char treeNodeSymbol(TREE* node)
{
    return node->symbol->symbol;
}

void printSymbolsFrequency(FILE* file, QUEUE* symbolsList)
{
    while(symbolsList)
    {
        fprintf(file, "%c%d ", queueMemberSymbol(symbolsList), queueMemberFreq(symbolsList));

        symbolsList = symbolsList->next;
    }

    return;
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

void printSymbolsCode(FILE* file, TREE* root)
{
    if(root->symbol->symbol)
    {
        fprintf(file, "%c %s\n", root->symbol->symbol, root->symbol->code);
    }

    if(root->left)
    {
        printSymbolsCode(file, root->left);
    }

    if(root->right)
    {
        printSymbolsCode(file, root->right);
    }
}
