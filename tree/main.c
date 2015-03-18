#include "head.h"

int main()
{
    int key = 0;
    int num = 0;
    int i = 0;
    TREE* root = NULL;

    fscanf(stdin, "%d", &num);

    for(i = 0; i < num; i++)
    {
        fscanf(stdin, "%d", &key);
        insertToTree(&root, key);
    }

    printHeight(root);
    deleteTree(&root);

    return 0;
}

void insertToTree(TREE** root, int val)
{
    if(!(*root))
    {
        (*root) = (TREE*)malloc(sizeof(TREE));
        memset((*root), 0, sizeof(TREE));
        (*root)->val = val;
        (*root)->height = 1;

        return;
    }

    if(val <= (*root)->val)
    {
        insertToTree(&(*root)->left, val);
    }

    if(val > (*root)->val)
    {
        insertToTree(&(*root)->right, val);
    }

    (*root) = balance((*root));

    return;
}

void deleteTree(TREE** root)
{
    if(!(*root))
    {
        return;
    }

    if((*root)->left)
    {
        deleteTree(&(*root)->left);
    }

    if((*root)->right)
    {
        deleteTree(&(*root)->right);
    }

    free((*root));

    return;
}

void printHeight(TREE* root)
{
    if(!root)
    {
        fprintf(stdout, "%d", 0);

        return;
    }

    fprintf(stdout, "%d", root->height);
}
