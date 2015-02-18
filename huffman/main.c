#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    int i = 0;
    int j = 0;
    int indexOfOutFile = 0;
    long position = 0;

    if((argc == 1))
    {
        puts("Too few parameters");

        return ERROR;
    }

    for(i = argc - 1; i > 1; i--)
    {
        if(argv[i][0] != PARAMETER)
        {
            indexOfOutFile = i;

            break;
        }
    }

    outFile = fopen(argv[indexOfOutFile], "a");

    fseek(outFile, 0, SEEK_END);
    position = ftell(outFile);

    if(position == EMPTY)
    {
        fputs("Huff!\t", outFile);
    }

    for(j = 1; j < argc; j++)
    {
        if(argv[j][0] == PARAMETER)
        {
            switch(argv[j][1])
            {
            case HELP:
                help();

                break;

            case ADD:
                for(i = 1; i < argc; i++)
                {
                    if((argv[i][0] != PARAMETER) && i != indexOfOutFile)
                    {
                        inFile = fopen(argv[i], "r");

                        if(!inFile)
                        {
                            printf("File %s not found", argv[1]);
                        }

                        fputs(argv[i], outFile);
                        pack(inFile, outFile);
                        fclose(inFile);
                    }
                }

                break;

            case EXT:
            case DEL:
            case LIST:
            case INTEGR:
                break;

            default:
                printf("%s unknown parameter\n", argv[1]);
            }
        }
    }

    fclose(outFile);

    return 0;
}
