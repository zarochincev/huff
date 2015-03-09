#include "head.h"

void sortList(SYMBOL* head)
{
    SYMBOL* temp = NULL;
    SYMBOL* tmp = NULL;
    int tempNum = 0;
    char tempCh = 0;

    for(temp = head; temp; temp = temp->next)
    {
        for(tmp = head; tmp; tmp = tmp->next)
        {
            if(temp->freq < tmp->freq)
            {
                tempNum = temp->freq;
                tempCh = temp->symbol;
                temp->freq = tmp->freq;
                temp->symbol = tmp->symbol;
                tmp->freq = tempNum;
                tmp->symbol = tempCh;
            }
        }
    }

    return;
}

void writeSymbolFreq(SYMBOL* sym, FILE* file)
{
    if(sym)
    {
        fprintf(file, "%c%d", sym->symbol, sym->freq);

        writeSymbolFreq(sym->next, file);
    }

    return;
}

QUEUE* dequeue(QUEUE** head)
{
    QUEUE* tmp = *head;

    *head = (*head)->next;

    return tmp;
}

void enqueue(QUEUE* sym, QUEUE* queue)
{
    while(getFreq(queue) <= getFreq(sym))
    {
        queue = queue->next;
    }

    sym->next = queue->next;
    queue->next = sym;

    return;
}

unsigned int getFreq(QUEUE* que)
{
    return que->node->symbol->freq;
}

QUEUE* createQueue(SYMBOL* sym)
{
    SYMBOL* tmpSym = sym;
    QUEUE* que = NULL;
    QUEUE* head = que;
    TREE* tmpNode = NULL;

    if(!head)
    {
        que = (QUEUE*)malloc(sizeof(QUEUE));

        memset(que, 0, sizeof(QUEUE));

        tmpNode = (TREE*)malloc(sizeof(TREE));

        memset(tmpNode, 0, sizeof(TREE));

        tmpNode->symbol = tmpSym;
        que->node = tmpNode;
        tmpSym = tmpSym->next;
        head = que;
    }

    if(sym->next)
    {
        head->next = createQueue(sym->next);
    }

    return head;
}
