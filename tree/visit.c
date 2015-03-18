#include "head.h"

void visitTree(TREE* root, FILE* file)
{
    if(!root)
    {
        return;
    }

    if(root->left)
    {
        visitTree(root->left, file);
        fprintf(file, "go left\n");
    }

    fprintf(file, "%d %d \n", root->val, root->height);

    if(root->right)
    {
        visitTree(root->right, file);
        fprintf(file, "go right\n");
    }

    return;
}
