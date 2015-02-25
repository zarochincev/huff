#include "head.h"

void help()
{
    puts("Archiver Huffman\n");
    puts("huffman.exe [/a] [/x] source [disk:][directory][file name] result [disk:][directory][file name]\n");
    puts("[disk:][directory][file name]\n");
    puts("\tdisk directory or file name for processing\n");
    puts("source\tname of file for processing\n");
    puts("result\tarchive name\n");
    puts("/a\tadd archive\n");
    puts("/x\textract\n");
    system("pause");
    exit(0);
}
