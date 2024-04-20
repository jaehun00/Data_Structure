# include <stdio.h>
# include <stdlib.h>

typedef struct _node
{
    int key;
    struct _node *next;
}node;

node *head, *tail;

void init_list(){
    head = (node*)calloc(1,sizeof(node));
    tail = (node*)calloc(1,sizeof(node));
    head -> next = tail;
    tail -> next = tail;
}

node *insert_after(int k, node *t)
{
    node *temp;
    temp = (node*)calloc(1,sizeof(node));
    temp->key = k;
    temp->next = t->next;
    t->next=temp;

    return temp;
}

int delete_next(node *t)
{
    node *temp;
    if(t->next==tail)
        return 0;
    temp = t->next;
    t->next = t->next->next;
    free(temp);

    return 1;
}

node *find_node(int k)
{
    node *temp;
    temp = head->next;
    while(temp->key != k && temp != tail)
        temp = temp->next;
    return temp;
}

int delete_node(int k)
{
    node *s, *p;
    p = head;
    s = p->next;
    while(s->key != k && s != tail)
    {
        p = p->next;
        s = p->next;
    }
    if(s != tail)
    {
        p->next = s->next;
        free(s);
        return 1;
    }
    else return 0;
}

node *insert_node(int t, int k)
{
    node *s, *p, *r;
    p = head;
    s = p->next;
    while(s->key != k && s != tail)
    {
        p = p->next;
        s = p->next;
    }
    if(s != tail)
    {
        r = (node *)calloc(1,sizeof(node));
        r->key = t;
        p->next = r;
        r->next = s; 
    }
    return p->next;
}

node *ordered_insert(int k)
{
    node *s, *p, *r;
    p = head;
    s = p->next;
    while(s->key <= k && s != tail)
    {
        p = p->next;
        s = p->next;
    }
    r = (node *)calloc(1,sizeof(node));
    r->key = k;
    p->next = r;
    r->next = s; 

    return r;   
}

node *delete_all()
{
    node *s;
    node *t;
    t = head->next;
    while(t != tail)
    {
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
    return head;
}

void print_list(node *t)
{
    while(t != tail)
    {
        printf("%-8d",t->key);
        t = t->next;
    }
}

void insert_nodes(int k)
{
    node *t;
    int i;
    t = (node *)calloc(1, sizeof(node));
    t->key = 1;
    head = t;
    for(i=2; i<=k; i++)
    {
        t->next = (node *)calloc(1, sizeof(node)); 
        t = t->next;
        t->key = i;
    }
}

void delete_after(node *t)
{
    node *s;
    s = t->next;
    t->next = t->next->next;
    free(s);
}

void josephus(int n, int m)
{
    node *t;
    int i;
    insert_nodes(n);
    t = head;
    printf("\nAnswer :  ");
    while(t != t->next)
    {
        for(i=0; i<m-1; i++)
        {
            t = t->next;
        }
        printf("%d ", t->next->key);
        delete_after(t);

    }
    printf("%d", t->key); //last node
}

/*
void main()
{
    node *t;
    init_list();
    ordered_insert(9);
    ordered_insert(3);
    ordered_insert(5);
    ordered_insert(1);
    ordered_insert(7);
    print_list(head);
    t = find_node(5);
    insert_after(6,t);
    print_list(head);
    

}
*/

void main()
{
    int n,m;

    printf("Enter N and M :");
    scanf("%d %d", &n, &m);

    josephus(n, m);
    
}



