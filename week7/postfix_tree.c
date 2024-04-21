# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct _node{
    int key;
    struct _node *left;
    struct _node *right;
}node;

typedef struct _stack{
    node *data;
    struct _stack *next;
}stack;

typedef struct _queue{
    node *data;
    struct _queue *prev;
    struct _queue *next;
}queue;

node *head, *tail;
stack *s_head, *s_tail;
queue *q_head, *q_tail;

void init_stack(){
    s_head = (stack *)calloc(1, sizeof(stack));
    s_tail = (stack *)calloc(1, sizeof(stack));
    s_head->next = s_tail;
    s_tail->next = s_tail;
}

void init_queue(){
    q_head = (queue *)calloc(1, sizeof(queue));
    q_tail = (queue *)calloc(1, sizeof(queue));
    q_head->next = q_tail;
    q_head->prev = q_head;
    q_tail->next = q_tail;
    q_tail->prev = q_head;
}

int is_stack_empty(){
    if(s_head->next == s_tail){
        return 1;
    }
    return 0;
}

int is_queue_empty(){
    if(q_head->next == q_tail){
        return 1;
    }
    return 0;
}

node *push(node *data){
    stack *t;
    if((t=(stack *)malloc(sizeof(stack)))==NULL){
        return NULL;
    }
    t->data = data;
    t->next = s_head->next;
    s_head->next = t;
    return data;
}

node *pop(){
    stack *t;
    node *data;
    t = s_head->next;
    if(t==s_tail){
        return NULL;
    }
    data = t->data;
    s_head->next = t->next;
    free(t);
    return data;
}

node *put(node *data){
    queue *t;
    if((t=(queue *)malloc(sizeof(queue)))==NULL){
        return NULL;
    }    
    t->data = data;
    q_tail->prev->next = t;
    t->prev = q_tail->prev;
    t->next = q_tail;
    q_tail->prev = t;
    return data;
}

node *get(){
    queue *t;
    node *data;
    t = q_head->next;
    if(t==q_tail){
        return NULL;
    }
    data = t->data;
    q_head->next = t->next;
    t->next->prev = q_head;
    free(t);
    return data;
}

void init_tree(){
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}

int is_operator(int k){
    return (k=='+' || k=='-' || k=='*' || k=='/');
}

node *make_parse_tree(char *p){
    node *t;
    while(*p){
        while(*p==' '){
            p++;
        }
        t = (node *)calloc(1, sizeof(node));
        t->key = *p;
        t->left = tail;
        t->right = tail;
        if(is_operator(*p)){
            t->right = pop();
            t->left = pop();
        }
        push(t);
        p++;    
    }
    return pop();
}

void visit(node *t){
    printf("%c",t->key);
}

void preorder_traverse(node *t){
    if(t!=tail) {
        visit(t);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void main(){
    char post[256];
    init_stack();
    init_tree();

    while(1){
        printf("\n\nInput postfix expression -> ");
        gets(post);

        if(*post == '\0') break;

        head->right = make_parse_tree(post);

        printf("\nPre-order traverse -> ");
        preorder_traverse(head->right);
        printf("\n%c",head->left->left->left);
    }
}