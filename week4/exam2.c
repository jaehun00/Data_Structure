#include <stdint.h>
#include <stdlib.h>

typedef struct _dnode
{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

void init_dlist()
{
    head = (dnode *)calloc(1, sizeof(dnode));
    tail = (dnode *)calloc(1, sizeof(dnode));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}

dnode *insert_dnode_ptr(int k, dnode *t)
{
    dnode *i;
    if(t==head) return NULL;
    i = (dnode *)calloc(1, sizeof(dnode));
    i->key = k;
    i->prev = t->prev;
    t->prev = i;
    i->next = t;

    return i;
}
