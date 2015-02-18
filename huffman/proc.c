#include "head.h"

void pack(FILE* inFile, FILE* outFile)
{
    SYMBOL* firstSym = countSym(inFile);
    SYMBOL* sym = firstSym;

    fputs("\n", outFile);

    while(sym)
    {
        fprintf(outFile, "%c %d\n", sym->symbol, sym->number);
        sym = sym->next;
    }

    fputs("\n", outFile);
}
