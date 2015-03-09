#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    int i = 0;

    if((argc == 1))
    {
        puts("Too few parameters");

        return ERROR;
    }

    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], DEBUG))
        {
            #define _DEBUG_
            #include "debug.h"
        }
    }

    for(i = 1; i < argc; i++)
    {
        if(argv[i][0] == PARAMETER)
        {
            if(argv[i][1] == HELP)
            {
                if(argv[i][2] == '\0')
                {
                    help();
                }
            }
        }
    }

    outFile = fopen(argv[3], "w");

    if(argv[1][0] == PARAMETER)
    {
        if(argv[1][1] == ADD)
        {
            if(argv[1][2] == '\0')
            {
                inFile = fopen(argv[2], "r");

                if(!inFile)
                {
                    printf("File %s not found", argv[1]);
                }

                pack(inFile, outFile);
                fclose(inFile);
            }
        }

        if(argv[1][1] == EXTRACT)
        {
           if(argv[1][2] == '\0')
            {
                /**< extracting process */
            }
        }
    }

    fclose(outFile);

    return 0;
}
