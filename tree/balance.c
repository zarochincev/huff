#include "head.h"

TREE* turnLeft(TREE* node)
{
    TREE* rightNode = node->right;

    node->right = rightNode->left;
    rightNode->left = node;

    restoreHeight(node);
    restoreHeight(rightNode);

    return rightNode;
}

TREE* turnRight(TREE* node)
{
    TREE* leftNode = node->left;

    node->left = leftNode->right;
    leftNode->right = node;

    restoreHeight(node);
    restoreHeight(leftNode);

    return leftNode;
}

int balanceFactor(TREE* node)
{
    if(node->left && node->right)
    {
        return (node->right->height - node->left->height);
    }

    if(!node->left && node->right)
    {
        return 1;
    }

    if(node->left && !node->right)
    {
        return -1;
    }

    return 0;
}

void restoreHeight(TREE* node)
{
    if(!node->left && !node->right)
    {
        node->height = 1;

        return;
    }

    if(!node->left)
    {
        node->height = node->right->height + 1;
    }

    if(!node->right)
    {
        node->height = node->left->height + 1;
    }

    if(node->left && node->right)
    {
        if(node->left->height > node->right->height)
        {
            node->height = node->left->height + 1;
        }else
        {
            node->height = node->right->height + 1;
        }
    }
}

TREE* balance(TREE* node)
{
    restoreHeight(node);

    if(balanceFactor(node) >= 1) /**< condition for small right rotate */
    {
        if(balanceFactor(node->right) < 0) /**< condition for big left rotate */
        {
            node->right = turnRight(node->right);
        }

        node = turnLeft(node);
    }

    if(balanceFactor(node) <= -1) /**< condition for small left rotate */
    {
        if(balanceFactor(node->left) > 0) /**< condition for big right rotate */
        {
            node->left = turnLeft(node->left);
        }

        node = turnRight(node);
    }

    return node;
}
