#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    HASH* pair = NULL;
    HASH** hashTable = NULL;

    int i = 0;
    char* requiredWord = NULL;

    inFile = fopen(argv[1], "r");

    if(!inFile)
    {
        __exit(INCORRECT_FILE, argv[1]);
    }

    outFile = fopen(argv[2], "w");

    if(!outFile)
    {
        __exit(INCORRECT_FILE, argv[2]);
    }

    hashTable = (HASH**)calloc(MAX_HASH_SIZE, sizeof(HASH));

    if(!hashTable)
    {
        __exit(MEMORY_IS_NOT_ALLOCATED, NULL);
    }

    for(i = 0; !feof(inFile); i++)
    {
        pair = (HASH*)malloc(sizeof(HASH));

        if(!pair)
        {
            __exit(MEMORY_IS_NOT_ALLOCATED, NULL);
        }

        memset(pair, 0, sizeof(HASH));

        pair->key = (char*)malloc(sizeof(char) * 256);

        if(!pair->key)
        {
            __exit(MEMORY_IS_NOT_ALLOCATED, NULL);
        }

        memset(pair->key, 0, sizeof(char));

        fscanf(inFile, "%s", pair->key);
        insertToHashTable(pair, hashTable);
    }

    printHash(hashTable, outFile);

    requiredWord = (char*)calloc(256, sizeof(char));
    scanf("%s", requiredWord);
    printf("%d ", findWord(hashTable, requiredWord));

    fclose(inFile);
    fclose(outFile);
    deleteWord(hashTable, requiredWord);

    outFile = fopen(argv[3], "w");

    if(!outFile)
    {
        __exit(INCORRECT_FILE, argv[3]);
    }

    printHash(hashTable, outFile);

    return 0;
}

void __exit(int error, char* fileName)
{
    switch(error)
    {
    case INCORRECT_FILE:
        printf("ERROR : %s incorrect file", fileName);
        exit(INCORRECT_FILE);

    case MEMORY_IS_NOT_ALLOCATED:
        puts("ERROR : memory is not allocated");
        exit(MEMORY_IS_NOT_ALLOCATED);
    }
}

void insertToHashTable(HASH* pair, HASH** hashTable)
{
    unsigned int index = hashFunc(pair->key);
    HASH* tmp = NULL;

    if(!hashTable[index])
    {
        hashTable[index] = pair;
        hashTable[index]->val = 1;

        return;
    }

    tmp = hashTable[index];

    if(!strcmp(tmp->key, pair->key))
    {
        tmp->val += 1;

        return;
    }

    while(tmp->next)
    {
        tmp = tmp->next;

        if(!strcmp(tmp->key, pair->key))
        {
            tmp->val += 1;

            return;
        }
    }

    tmp->next = pair;
    tmp->next->val = 1;

    return;
}

int hashFunc(char* key)
{
    unsigned long long index = 0;
    int i = 0;
    for (i = 0; key[i]; i++)
    {
        index += index * 255 + key[i];
    }

    return ((int)(index % MAX_HASH_SIZE));
}

int findWord(HASH** table, char*key)
{
    int index = hashFunc(key);
    HASH* head = NULL;

    if(!table[index])
    {
        return 0;
    }

    head = table[index];

    if(!strcmp(head->key, key))
    {
        return head->val;
    }


    while(strcmp(head->key, key))
    {
        head = head->next;
    }

    if(!head)
    {
        return 0;
    }

    return head->val;
}

void deleteWord(HASH** table, char* key)
{
    int index = hashFunc(key);
    HASH* tmp;

    if(!table[index])
    {
        return;
    }

    tmp = table[index];

    if(!strcmp(table[index]->key, key))
    {
        if(tmp->next)
        {
            table[index] = tmp->next;

            memset(tmp, 0, sizeof(HASH));
        }

        free(table[index]);
    }
}

void printHash(HASH** table, FILE* file)
{
    int i = 0;
    HASH* tmp = NULL;

    for(i = 0; i < MAX_HASH_SIZE; i++)
    {
        tmp = table[i];

        while(tmp)
        {
            fprintf(file, "%d %d %s\n", hashFunc(tmp->key), tmp->val, tmp->key);

            tmp = tmp->next;
        }
    }
}
