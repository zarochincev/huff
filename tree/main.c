#include "head.h"

int main()
{
    int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    TREE* root = NULL;
    TREE* node = NULL;

    for(i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
        createNode(&node, arr[i]);
        createTree(&root, node);
    }

    printTree(root);

    return 0;
}

void createNode(TREE** node, int val)
{
    (*node) = (TREE*)malloc(sizeof(TREE));

    (*node)->val = val;
    (*node)->left = NULL;
    (*node)->right = NULL;
}

void createTree(TREE** root, TREE* node)
{
    if(!(*root))
    {
        (*root) = node;

        return;
    }

    if(node->val <= (*root)->val)
    {
        createTree(&(*root)->left, node);
    }

    if(node->val > (*root)->val)
    {
        createTree(&(*root)->right, node);
    }
}

void printTree(TREE* node)
{
    printf("%d ", node->val);

    if(node->left)
    {
        printTree(node->left);
    }else if(node->right)
    {
        printTree(node->right);
    }

    return;
}
