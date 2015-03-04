#include "head.h"

void pack(FILE* inFile, FILE* outFile)
{
    SYMBOL* firstSym = countSymFreq(inFile);
    TREE* root = NULL;
    QUEUE* queue = NULL;

    sortList(firstSym);
    writeSymbolFreq(firstSym, outFile);

    queue = createQueue(firstSym);
    root = createTree(queue);

    #ifdef _DEBUG_

    printTree(root);

    #endif /* _DEBUG_*/
}

SYMBOL* countSymFreq(FILE* inFile)
{
    SYMBOL* sym = NULL;
    SYMBOL* firstSym = NULL;
    char chr = 0;
    int numDiffSym = 0;

    while((chr = fgetc(inFile)) != EOF)
    {
        if(!firstSym)
        {
            firstSym = (SYMBOL*)malloc(sizeof(SYMBOL));

            memset(firstSym, 0, sizeof(SYMBOL));

            firstSym->symbol = chr;
            firstSym->freq = 1;
            sym = firstSym;

            numDiffSym++;

            continue;
        }

        while(sym)
        {
            if(chr == sym->symbol)
            {
                sym->freq += 1;
                sym = firstSym;

                break;
            }else if(sym->next)
            {
                sym = sym->next;

                continue;
            }else
            {
                sym->next = (SYMBOL*)malloc(sizeof(SYMBOL));

                memset(sym->next, 0, sizeof(SYMBOL));

                sym = sym->next;
                sym->symbol = chr;
                sym->freq = 1;
                sym = firstSym;

                numDiffSym++;

                break;
            }
        }
    }

    return firstSym;
}

TREE* createTree(QUEUE* sym)
{
    TREE* node = NULL;
    QUEUE* firstChild = NULL;
    QUEUE* secondChild = NULL;
    QUEUE* emptySymbol = NULL;

    while(sym)
    {
        if(sym->next)
        {
            firstChild = dequeue(&sym);
            secondChild = dequeue(&sym);
            node = (TREE*)malloc(sizeof(TREE));
            node->left = firstChild->node;
            node->right = secondChild->node;
            emptySymbol = (QUEUE*)malloc(sizeof(QUEUE));

            memset(emptySymbol, 0, sizeof(QUEUE));

            emptySymbol->node->symbol->freq = getFreq(firstChild) + getFreq(secondChild);

            enqueue(emptySymbol, sym);
        }
    }

    return node;
}
