#include "head.h"

void __exit(int errorCode, char* errorParameter)
{
    switch(errorCode)
    {
    case TOO_FEW_PARAMETERS:
        puts("ERROR : Too few parameters\nUse \"-?\" for help");
        exit(TOO_FEW_PARAMETERS);

    case UNKNOWN_PARAMETER:
        printf("ERROR : Unknown parameter %s\nUse \"-?\" for help", errorParameter);
        exit(UNKNOWN_PARAMETER);

    case TOO_MANY_PARAMETERS:
        puts("ERROR : Too many parameters\nUse \"-?\" for help");
        exit(TOO_MANY_PARAMETERS);

    case INVALID_FILE:
        printf("ERROR : %s invalid file", errorParameter);
        exit(INVALID_FILE);
    }
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
