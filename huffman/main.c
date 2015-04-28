#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inputFile = NULL;
    FILE* outputFile = NULL;
    char* outFileName = NULL;

    switch(argc)
    {
    case ONLY_PROGRAMM_NAME:
        __exit(TOO_FEW_PARAMETERS, NULL);

    case ONE_PARAMETER:
        if(argv[1][0] == PARAMETER)
        {
            if(argv[1][2])
            {
                __exit(UNKNOWN_PARAMETER, argv[1]);
            }

            if(argv[1][1] == HELP)
            {
                help();
            }else
            {
                __exit(TOO_FEW_PARAMETERS, NULL);
            }
        }else /**< argv[1][0] != PARAMETER */
        {
            __exit(UNKNOWN_PARAMETER, argv[1]);
        }

        break;

    case TWO_PARAMETERS:
        if(argv[1][0] == PARAMETER)
        {
            if(argv[1][2])
            {
                __exit(UNKNOWN_PARAMETER, argv[1]);
            }

            switch(argv[1][1])
            {
            case ARCHIVE:
                inputFile = fopen(argv[2], "rb");

                if(!inputFile)
                {
                    __exit(INVALID_FILE, argv[2]);
                }

                outFileName = createFileName(argv[2]);

                outputFile = fopen(outFileName, "w");

                if(!outputFile)
                {
                    __exit(INVALID_FILE, outFileName);
                }

                pack(inputFile, outputFile);

                fclose(inputFile);
                fclose(outputFile);

                break;

            case EXTRACT:
                inputFile = fopen(argv[2], "rb");

                if(!inputFile)
                {
                    __exit(INVALID_FILE, argv[2]);
                }

                outFileName = createFileName(argv[2]);

                outputFile = fopen(outFileName, "w");

                if(!outputFile)
                {
                    __exit(INVALID_FILE, outFileName);
                }

                extract();

                fclose(inputFile);
                fclose(outputFile);

                break;

            case HELP:
                help();

                break;

            default:
                __exit(UNKNOWN_PARAMETER, argv[1]);

                break;
            }/**< switch argv[1][1] */
        }else/**< argv[1][0] != PARAMETER */
        {
            __exit(UNKNOWN_PARAMETER, argv[1]);
        }
        break;

    case TREE_PARAMETERS:
        if(argv[1][0] == PARAMETER)
        {
            if(argv[1][2])
            {
                __exit(UNKNOWN_PARAMETER, argv[1]);
            }

            switch(argv[1][1])
            {
            case ARCHIVE:
                inputFile = fopen(argv[2], "rb");

                if(!inputFile)
                {
                    __exit(INVALID_FILE, argv[2]);
                }

                outputFile = fopen(argv[3], "w");

                if(!outputFile)
                {
                    __exit(INVALID_FILE, argv[3]);
                }

                pack(inputFile, outputFile);

                fclose(inputFile);
                fclose(outputFile);

                break;

            case EXTRACT:
                inputFile = fopen(argv[2], "rb");

                if(!inputFile)
                {
                    __exit(INVALID_FILE, argv[2]);
                }

                outputFile = fopen(argv[3], "w");

                if(!outputFile)
                {
                    __exit(INVALID_FILE, argv[3]);
                }

                extract();

                fclose(inputFile);
                fclose(outputFile);

                break;

            case HELP:
                help();

                break;

            default:
                __exit(UNKNOWN_PARAMETER, argv[1]);

                break;
            }/**< switch argv[1][1] */
        }else/**< argv[1][0] != PARAMETER */
        {
            __exit(UNKNOWN_PARAMETER, argv[1]);
        }
        break;

    default:
        __exit(TOO_MANY_PARAMETERS, NULL);
    }/**< switch argc */

    __exit(SUCCESS, NULL);

    return 0;
}
