#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    HASH* pair = NULL;
    HASH** hashTable = NULL;
    HASH* tmp = NULL;
    int i = 0;

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

        pair->val = (char*)malloc(sizeof(char) * 256);

        if(!pair->val)
        {
            __exit(MEMORY_IS_NOT_ALLOCATED, NULL);
        }

        memset(pair->val, 0, sizeof(char));

        fscanf(inFile, "%d%s", &pair->key, pair->val);
        insertToHashTable(pair, hashTable);
    }

    for(i = 0; i < MAX_HASH_SIZE; i++)
    {
        tmp = hashTable[i];

        while(tmp)
        {
            fprintf(outFile, "%d %d %s\n", hashFunc(tmp->key), tmp->key, tmp->val);

            tmp = tmp->next;
        }
    }

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
    int index = hashFunc(pair->key);
    HASH* tmp = NULL;

    if(!hashTable[index])
    {
        hashTable[index] = pair;

        return;
    }

    tmp = hashTable[index];

    while(tmp->next)
    {
        tmp = tmp->next;
    }

    tmp->next = pair;
}

int hashFunc(int key)
{
    return (key % MAX_HASH_SIZE);
}
