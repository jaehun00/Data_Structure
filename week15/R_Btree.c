#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define BASE(i) ((char *)base + (i)*width)
#define SEQ 10

typedef struct _node{
    struct _node *left;
    struct _node *right;
    int red; 
}node;

node *head;

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}
int charcmp(const void *a, const void *b){
    return (*(char *)a- *(char *)b);
}

void init_tree(node **);
void visit(node *);
void inorder_traverse(node *);
node *rotate(void *, node *, node *, FCMP fcmp);
node *rbti_insert(void *, node *, int *, int width, FCMP fcmp);

void main(){
    char data[SEQ];
    char str[] = "KLCAEFDIHG";
    int i;

    for(i = 0; i < SEQ; i++){
        data[i] = str[i];
    }

    for(i = 0; i < SEQ; i++){
        printf("%c", data[i]);
    }
    printf("\n");

    node *t, *p;

    init_tree(&t);
    head = t;
    
    int size = 0;
    for(i = 0; i < SEQ; i++){
        p = head;
        p = rbti_insert(&data[i], p, &size, sizeof(char), charcmp);
    }

    printf("\ndone\n");
    t = head->left;
    inorder_traverse(t);

}

void init_tree(node **p){
    *p = (node *)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
}

void visit(node *t){
    printf("%c", *(char *)(t+1));
}

void inorder_traverse(node *p){
    if(p!=NULL){
        inorder_traverse(p->left);
        visit(p);
        inorder_traverse(p->right);
    }
}

node *rotate(void *key, node *pivot, node *base, FCMP fcmp){
    node *child, *gchild;
    if(fcmp(key, pivot + 1) < 0 || pivot == head)
        child = pivot->left;
    else
        child = pivot->right;
    
    if(fcmp(key, child + 1) < 0){
        gchild = child->left;
        child->left = gchild->right;
        gchild->right = child;
    }
    else{
        gchild = child->right;
        child->right = gchild->left;
        gchild->left = child;
    }

    if(fcmp(key, pivot + 1) < 0 || pivot == base)
        pivot->left = gchild;
    else
        pivot->right = gchild;

    return gchild;
}

node *rbti_insert(void *key, node *base, int *num, int width, FCMP fcmp){
    node *t, *parent, *gparent, *ggparent;
    ggparent = gparent = parent = base;
    t = base->left;

    // key 위치
    while(t != NULL){
        if(fcmp(key, t + 1) == 0) return NULL;

        if(t->left && t->right && t->left->red && t->right->red){
            t->red = 1;
            t->left->red = t->right->red = 0;
            if(parent->red){
                gparent->red = 1;
                if((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
                    parent = rotate(key, gparent, base, fcmp);
                t = rotate(key, ggparent, base, fcmp);
                t->red = 0;
            }
            base->left->red = 0;
        }
        ggparent = gparent;
        gparent = parent;
        parent = t;
        if(fcmp(key, t + 1) < 0) t = t->left;
        else t = t->right;
    }
    
    // key 삽입
    t = (node *)malloc(sizeof(node));
    memcpy(t + 1, key, width);
    t->left = NULL;
    t->right = NULL;
    if(fcmp(key, parent + 1) < 0 || parent == base) parent->left = t;
    else parent->right = t;
    (*num)++;
    t->red = 1;

    if(parent->red){
        gparent->red = 1;
        if((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
            parent = rotate(key, gparent, base, fcmp);
        t = rotate(key, ggparent, base, fcmp);
        t->red = 0;
    }
    base->left->red = 0;

    return t;
}