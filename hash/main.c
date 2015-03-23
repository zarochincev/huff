#include "head.h"

int main()
{
    int numOfWords = 0;
    HASH* word = NULL;
    HASH* hashMap[MAX_HASH_SIZE];
    int i = 0;

    for(i = 0; i < MAX_HASH_SIZE; i++)
    {
        hashMap[i] = (HASH*)calloc(1, sizeof(HASH));
    }

    scanf("%d", &numOfWords);

    for(; numOfWords > 0; numOfWords--)
    {
        generateWord(&word);
        insertToHash(word, hashMap);
    }

    for(i = 0; i < MAX_HASH_SIZE; i++)
    {
        printf("%d) %s\n", i, hashMap[i]->val);
    }

    return 0;
}

int hashFunc(char* key)
{
    int result = 0;
    int i = 0;

    for(i = 0; key[i]; i++)
    {
        result += (result * 255) + key[i];
    }

    return result;
}

void generateWord(HASH** word)
{
    static int prevSeed = 0;
    int __seed = 0;
    int i = 0;
    char* val = (char*)calloc(1, sizeof(char) * WORD_LENGHT_WITH_FINEL_ZERO);
    char* key = (char*)calloc(1, sizeof(char) * KEY_LENGHT_WITH_FINEL_ZERO);

    *word = (HASH*)calloc(1, sizeof(HASH));

    __seed = time(NULL);

    while(__seed == prevSeed)
    {
        __seed = time(NULL);
    }

    prevSeed = __seed;

    srand(__seed);

    for(i = 0; i < WORD_LENGHT; i++)
    {
        val[i] = rand() % ('z' - 'a') + 'a';
    }

    val[WORD_LENGHT] = '\0';

    key = strncpy(key, val, KEY_LENGHT);

    key[KEY_LENGHT] = '\0';

    (*word)->val = val;
    (*word)->key = key;
    (*word)->next = NULL;
}

void insertToHash(HASH* word, HASH* hashMap[MAX_HASH_SIZE])
{
    hashMap[hashFunc(word->key) % MAX_HASH_SIZE] = word;
}

char* findWord(char* key, HASH* hashMap[MAX_HASH_SIZE])
{
    return (hashMap[hashFunc(key) % MAX_HASH_SIZE]->val);
}

void deledeWord(char* key, HASH* hashMap[MAX_HASH_SIZE])
{
    memset(hashMap[hashFunc(key) % MAX_HASH_SIZE], 0, sizeof(HASH));
}
