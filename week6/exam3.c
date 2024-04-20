#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _dnode
{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

void init_queue()
{
    head = (dnode *)calloc(1, sizeof(dnode));
    tail = (dnode *)calloc(1, sizeof(dnode));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}

int put(int k)
{
    dnode *t;
    if((t = (dnode *)malloc(sizeof(dnode)))==NULL)
    {
        printf("Out of memory !\n");
        return -1;
    }
    t->key = k;
    tail->prev->next = t;
    t->prev = tail->prev;
    tail->prev = t;
    t->next = tail;
    return k;
}

int get()
{
    dnode *t;
    int k;
    t = head->next;
    if(t == tail)
    {
        printf("Queue underflow! \n");
        return -1;
    }
    k = t->key;
    head->next = t->next;
    t->next->prev = head;
    free(t);
    return k;
}

void clear_queue()
{
    dnode *t, *s;
    t = head->next;

    while(t != tail)
    {
        s = t;
        t = t->next;
        free(s);
    }

    head->next = tail;
    tail->prev = head;
}

void print_queue()
{
    dnode *t;
    t = head->next;
    while(t != tail)
    {
        printf("%-6d", t->key);
        t = t->next;
    }
}

void main()
{
    int k;
    init_queue();
    put(3);
    put(6);
    put(9);
    put(1);
    put(6);
    put(3);
    print_queue();
    get();
    get();
    print_queue();
}