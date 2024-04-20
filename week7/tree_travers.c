#include <stdio.h>
#include <stdlib.h>

typedef struct  _node
{
    int key;
    struct _node *left;
    struct _node *right;
}node;

node *head, *tail;

void init_tree()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}

void preorder_traverse(node *t)
{
    if(t != tail)
    {
        visit(t);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}
