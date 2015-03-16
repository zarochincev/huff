#include "head.h"

void visitTree(TREE* root)
{
    if(!root)
    {
        return;
    }

    if(root->left)
    {
        visitTree(root->left);
    }

    if(root->right)
    {
        visitTree(root->right);
    }

    return;
}
