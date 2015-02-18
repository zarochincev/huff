#include "head.h"

SYMBOL* countSym(FILE* inFile)
{
    SYMBOL* sym = NULL;
    SYMBOL* firstSym = NULL;
    char ch = 0;
    int numDiffSym = 0;

    while((ch = fgetc(inFile)) != EOF)
    {
        if(!firstSym)
        {
            firstSym = (SYMBOL*)malloc(sizeof(SYMBOL));
            firstSym->symbol = ch;
            firstSym->number = 1;
            firstSym->next = NULL;
            sym = firstSym;
            numDiffSym++;

            continue;
        }

        while(sym)
        {
            if(ch == sym->symbol)
            {
                sym->number += 1;
                sym = firstSym;

                break;
            }else if(sym->next)
            {
                sym = sym->next;

                continue;
            }else
            {
                sym->next = (SYMBOL*)malloc(sizeof(SYMBOL));
                sym = sym->next;
                sym->symbol = ch;
                sym->number = 1;
                sym->next = NULL;
                sym = firstSym;
                numDiffSym++;

                break;
            }
        }
    }

    sortList(firstSym);

    return firstSym;
}

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
            if(temp->number > tmp->number)
            {
                tempNum = temp->number;
                tempCh = temp->symbol;
                temp->number = tmp->number;
                temp->symbol = tmp->symbol;
                tmp->number = tempNum;
                tmp->symbol = tempCh;
            }
        }
    }
}
