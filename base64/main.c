#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    int i = 0;

    if(argc == 1)
    {
        __exit(FEW_PAR, NULL);
    }

    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], HELP))
        {
            help();
        }
    }

    if(argc < 4) /*4 parameters (*.exe, mode, input, output)*/
    {
        __exit(FEW_PAR, NULL);
    }

    if(argc > 4) /*4 parameters (*.exe, mode, input, output)*/
    {
        __exit(MANY_PAR, NULL);
    }

    if(strcmp(argv[1], ENCODE) && strcmp(argv[1], DECODE))
    {
        __exit(UNKNOWN_PAR, argv[1]);
    }

    inFile = fopen(argv[2], "rb");

    if(!inFile)
    {
        __exit(FILE_NOT_FOUND, argv[2]);
    }

    outFile = fopen(argv[3], "wb");

    if(!strcmp(argv[1], ENCODE))
    {
        encode(inFile, outFile);
    }

    if(!strcmp(argv[1], DECODE))
    {
        checkB64File(inFile) ? decode(inFile, outFile) : __exit(INV_FILE, argv[2]);
    }

    fclose(inFile);
    fclose(outFile);

    return 0;
}
