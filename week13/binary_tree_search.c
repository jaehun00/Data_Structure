# include <stdio.h>
# include <stdlib.h>
# include <windows.h>

#define MAX 100
#define SEQ 12

typedef struct _node{
    struct _node *left;
    struct _node *right;
}node;

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}
int charcmp(const void *a, const void *b){
    return (*(char *)a- *(char *)b);
}

void init_tree(node **);
node *bti_search(void *, node *, int *, int width, FCMP fcmp);
node *bti_insert(void *, node *, int *, int width, FCMP fcmp);
node *bti_delete(void *, node *, int *, int width, FCMP fcmp);
node *bti_delete_compact(void *, node *, int *, int width, FCMP fcmp);

void main() {
    char data[SEQ];
    char str[] = "FBOADCLGMHN";
    int i;

    for (i = 0; i < SEQ; i++) {
        data[i] = str[i];
    }

    // 배열에 저장된 문자 출력
    for (i = 0; i < SEQ; i++) {
        printf("%c ", data[i]);
    }
    printf("\n");

    node *t, *p, *d, *head;
    init_tree(&t);
    head = t;

    int size = 0;
    for (i = 0; i < SEQ; i++) {
        t = head;
        t = bti_insert(&data[i], t, &size, sizeof(char), charcmp);
    }

    char key = 'K';
    t = head;
    t = bti_insert(&key, t, &size, sizeof(char), charcmp);

    int pos = 0;
    t = head;
    p = bti_search(&key, t, &pos, sizeof(char), charcmp);
    printf("%c, %d\n", *(char *)(p + 1), pos);

    int del = 0;
    key = 'C';
    t = head;
    d = bti_delete_compact(&key, t, &del, sizeof(char), charcmp);
    key = 'M';
    t = head;
    d = bti_delete_compact(&key, t, &del, sizeof(char), charcmp);
    key = 'B';
    t = head;
    d = bti_delete_compact(&key, t, &del, sizeof(char), charcmp);
    key = 'F';
    t = head;
    d = bti_delete_compact(&key, t, &del, sizeof(char), charcmp);

    t = head->left;
    printf("%c\n", *(t+1));
    t = head->left->left;
    printf("%c\n", *(t+1));
}

void init_tree(node **p){
    *p = (node *)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
}

node *bti_search(void  *key, node *base, int *pos, int widht, FCMP fcmp){
    node *s;
    s = base->left;
    while(fcmp(key,s+1) != 0 && s != NULL){
        if(fcmp(key,s+1) < 0) s = s->left;
        else s = s->right;
        (*pos)++;
    }
    if(s == NULL) return NULL;
    else return s;
}

node *bti_insert(void *key, node *base, int *num, int width, FCMP fcmp){
    node *p, *s;
    p = base;
    s = base->left;
    while(s != NULL){
        p = s;
        if(fcmp(key,s+1) < 0) s = s->left;
        else s = s->right;
    }
    // s == NULL
	if ((s = (node*)malloc(sizeof(node) + width)) == NULL)
		return NULL;
    memcpy(s+1, key, width);
    s->left = NULL;
    s->right = NULL;

    if(fcmp(key,p+1) < 0 || p == base) p->left = s;
    else p->right = s;
    (*num)++;
    return s;
}

node *bti_delete(void *key, node *base, int *num, int width, FCMP fcmp){
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    while(fcmp(key, del+1) != 0 && del != NULL){
        parent = del;
        if(fcmp(del+1, key) > 0) del = del->left;
        else del = del->right;
    }
    if(del == NULL) return NULL;

    // CASE 1
    if(del->left == NULL && del->right == NULL){
        son = NULL;
        printf("Do CASE 1\n");
    }
    // CASE 3
    else if(del->left != NULL && del->right != NULL){
        nexth = del->right; // right first
        // CASE 3-2
        if(nexth->left != NULL){
            while(nexth->left->left != NULL) nexth = nexth->left;  
            son = nexth->left;
            nexth->left = son->right;
            son->left = del->left;
            son->right = del->right;
            printf("DO CASE 3-2\n");
        }
        // CASE 3-1
        else{
            son = nexth;
            son->left = del->left;
            printf("DO CASE 3-1\n");
        }
    }
    //CASE 2
    else{
        if(del->left != NULL) son = del->left;
        else son = del->right;
        printf("DO CASE 2\n");
    }

    if(fcmp(key, parent+1) < 0 || parent == base)
        parent->left = son;
    else
        parent->right = son;

    free(del);
    (*num)--;

    return parent;
}

node *bti_delete_compact(void *key, node *base, int *num, int width, FCMP fcmp){
    // Find delete node
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    while(fcmp(key, del+1) != 0 && del != NULL){
        parent = del;
        if(fcmp(del+1, key) > 0) del = del->left;
        else del = del->right;
    }

    //No right child
    if(del == NULL) return NULL;
    if(del->left == NULL) son = del->left;

    // No right->left
    else if(del->right->left == NULL){
        son = del->right;
        son->left = del->left;
    }

    // otherwise
    else{
        nexth = del->right;
        while(nexth->left->left != NULL) nexth = nexth->left;
        son = nexth->left;
        nexth->left = son->right;
        son->left = del->left;
        son->right = del->right;
    }

        if(fcmp(key, parent+1) < 0 || parent == base)
        parent->left = son;
    else
        parent->right = son;

    free(del);
    (*num)--;

    return parent;
}