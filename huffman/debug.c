#include "head.h"

#ifdef _DEBUG_HUFF_TREE_

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

#endif /*_DEBUG_HUFF_TREE_*/

#ifdef _DEBUG_HUFF_QUEUE_

void printQueue(QUEUE* queue)
{
    FILE* err = fopen("err.txt", "a");

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

#endif /*_DEBUG_HUFF_QUEUE_*/
