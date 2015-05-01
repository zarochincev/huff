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
    }

    while(_queue)
    {
        if(node->symbol->frequency <= _queue->node->symbol->frequency)
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
        }else
        {
            if(!_queue->next)
            {
                tmp->node = node;
                _queue->next = tmp;
                _queue = *head;

                break;
            }
        }

        prevQueue = _queue;
        _queue = _queue->next;
    }/**< while(_queue) */
}
