#include "head.h"

int main(int argc, char* argv[])
{
    FILE* inFile = NULL;
    FILE* outFile = NULL;
    int key = 0;
    TREE* root = NULL;
    TREE* node = NULL;

    if(argc != 3)
    {
        puts("incorrect parameters");

        return 0;
    }

    inFile = fopen(argv[1], "r");

    if(!inFile)
    {
        printf("file %s not found", argv[1]);

        return 0;
    }

    outFile = fopen(argv[2], "w");

    while(!feof(inFile))
    {
        fscanf(inFile, "%d", &key);
        createNode(&node, key);
        createTree(&root, node);
    }

    visitTree(root);

    fprintf(outFile, "%d", root->height);

    return 0;
}

void createNode(TREE** node, int val)
{
    (*node) = (TREE*)malloc(sizeof(TREE));

    (*node)->val = val;
    (*node)->height = 1;
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

    (*root) = balance((*root));
}

void deleteTree(TREE* root)
{
    if(!root)
    {
        return;
    }

    if(root->left)
    {
        deleteTree(root->left);
    }

    if(root->right)
    {
        deleteTree(root->right);
    }

    free(root);

    return;
}
