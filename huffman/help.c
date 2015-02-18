#include "head.h"

void help()
{
    puts("Archiver Huffman\n");
    puts("huffman.exe [/a] [/x] [/d] [/l] [/t] source [disk:][directory][file name] result [disk:][directory][file name]\n");
    puts("[disk:][directory][file name]\n");
    puts("\tdisk directory or file names for processing\n");
    puts("source\tnames of one or more files for processing\n");
    puts("result\tarchive name\n");
    puts("/a\tadd archive\n");
    puts("/x\textract\n");
    puts("/d\tdelete from archive\n");
    puts("/l\tdisplay a list of files in the archive\n");
    puts("/t\tcheck archive integrity\n");
    system("pause");
    exit(0);
}
