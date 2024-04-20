# include <stdio.h>
# include <stdlib.h>

typedef struct _node{
    int key;
    struct _node *next;
}node;

node *head, *tail;

void init_list(){
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

// insert node after node *t
node *insert_after(int k, node *t){
    node *temp;
    temp = (node *)calloc(1, sizeof(node));
    temp->key = k;
    temp->next = t->next;
    t->next = temp;

    return temp;
}

// delete the next node of t
// check next node is not tail node
int delete_next(node *t){
    node *temp;
    if(t->next==tail){
        return 0;
    }
    temp = t->next;
    t->next = t->next->next;
    free(temp);
    
    return 1;
}

// find the node containing a given key value
node *find_node(int k){
    node *temp;
    temp = head->next;

    while(temp->key!=k && temp!=tail){
        temp = temp->next;
    }

    return temp;
}

// delete node contatining a given key value
int delete_node(int k){
    node *p, *s;    // node p is previous node, node s is for delete  
    p = head;
    s = p->next;
    while(s->key!=k && s!=tail){
        p = p->next;
        s = p->next;
    }
    if(s!=tail){
        p->next = s->next;
        free(s);
        return 1;
    }
    else return 0;  // there's no k
}

// insert node containing a given key value
// insert t before k
node *insert_node(int t, int k){
    node *p, *s, *r;
    p = head;
    s = p->next;
    while(s->key!=k && s!=tail){
        p = p->next;
        s = p->next;
    }
    if(s!=tail){
        r = (node *)calloc(1, sizeof(node));
        r->key = t;
        p->next = r;
        r->next = s;
    }
    return p->next;
}
// ordered sorting in the linked list
node *ordered_insert(int k){
    node *s, *p, *r;
    p = head;
    s = p->next;
    while(s->key<=k && s!=tail){
        p = p->next;
        s = p->next;
    }
    r = (node *)calloc(1, sizeof(node));
    r->key = k;
    p->next = r;
    r->next = s;
    return r;
}

node *delete_all(){
    node *s, *t;
    t = head->next;
    while(t!=tail){
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
    return head;
}

void print_list(node *t){
    while(t!=tail){
        printf("%-8d", t->key);
        t = t->next;
    }
}

void main(){
    node *t;
    init_list();

    ordered_insert(9);
    ordered_insert(3);
    ordered_insert(1);

    print_list(head->next);
    
}

