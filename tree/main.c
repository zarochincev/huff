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

    visitTree(root);

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

void visitTree(TREE* root)
{
    QUEUE* queue = NULL;

    if(!root)
    {
        return;
    }

    queue = (QUEUE*)malloc(sizeof(QUEUE));

    enqueue(root, queue);

    while(!isEmptyQueue(queue))
    {
        printf("%d ", queue->node->val);
        dequeue(&queue);

        if(root->left)
        {
            visitTree(root->left);
        }

        if(root->right)
        {
            visitTree(root->right);
        }
    }
}

void enqueue(TREE* node, QUEUE* queue)
{
    QUEUE* tmp = (QUEUE*)malloc(sizeof(QUEUE));

    while(queue->next)
    {
        queue = queue->next;
    }

    tmp->node = node;
    tmp->next = NULL;
    queue->next = tmp;

    return;
}

void dequeue(QUEUE** queue)
{
    QUEUE* tmp = (*queue);

    (*queue) = (*queue)->next;

    free(tmp);

    return;
}

int isEmptyQueue(QUEUE* queue)
{
    return (queue ? 1 : 0);
}
