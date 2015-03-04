#include "debug.h"

void printTree(TREE* root)
{
    FILE* err = fopen("err.txt", "w");

    if(!root)
    {
        return;
    }

    fprintf(err, "%d ", root->symbol->freq);

    if(root->left)
    {
        printTree(root->left);
    }

    if(root->right)
    {
        printTree(root->right);
    }
}
