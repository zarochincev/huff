#include "debug.h"

void printTree(TREE* root)
{
    FILE* err = fopen("err.txt", "a");

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

void printQueue(QUEUE* queue)
{
    FILE* err = fopen("err.txt", "a");
puts("!!!");
    if(!queue)
    {
        return;
    }

    fprintf(err, "%c ", queue->node->symbol->symbol);

    if(queue->next)
    {
        printQueue(queue->next);
    }
}
