#include "head.h"

void help()
{
    puts("BASE64 converter\n");
    puts("base64.exe [/e] [/d] source [file name] result [file name]\n");
    puts("[file name]\tname of file for processing\n");
    puts("source\t source file name\n");
    puts("result\tconverted file name");
    puts("/e\tconvert file to BASE64\n");
    puts("/d\tconvert file from BASE64\n");
    system("pause");
    exit(0);
}
