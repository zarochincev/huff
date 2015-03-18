#include "head.h"

int main(/*int argc, char* argv[]*/)
{
    FILE* inFile = fopen("in.txt", "r");
    /*FILE* outFile = NULL;*/
    int key = 0;
    int num = 0;
    int i = 0;
    TREE* root = NULL;
    TREE* node = NULL;
/*    FILE* debugFile = fopen("debugFile.txt", "w");*/

    /*if(argc != 3)
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
    }*/

    /*fscanf(stdin, "%d", &num); */
    fscanf(inFile, "%d", &num);

    /*fprintf(debugFile, "!%d!\n", num);*/

    for(i = 0; i < num; i++)
    {
        fscanf(inFile, "%d", &key);
        /*fscanf(stdin, "%d", &key);*/
        createNode(&node, key);
        createTree(&root, node);
    }

    printHeight(root);
    deleteTree(root);
    /*visitTree(root, debugFile);*/

    return 0;
}

void createNode(TREE** node, int val)
{
    (*node) = (TREE*)malloc(sizeof(TREE));

    memset((*node), 0, sizeof(TREE));

    (*node)->val = val;
    (*node)->height = 1;
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

void printHeight(TREE* root)
{
    if(!root)
    {
        fprintf(stdout, "%d", 0);

        return;
    }

    fprintf(stdout, "%d", root->height);
}
