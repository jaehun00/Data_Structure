# include <stdio.h>
# include <stdlib.h>

typedef struct _node{
    char key;
    struct _node *next;
}node;

node *head;

void insert_nodes(char ch){
    node *t;
    char start = 'A';
    t = (node *)calloc(1, sizeof(node));
    t->key = start++;
    head = t;
    do{
        t->next = (node *)calloc(1, sizeof(node));
        t = t->next;
        t->key = start++;
    }while(start<=ch);
    t->next = head;
}

void delete_after(node *t){
    node *s;
    s = t->next;
    t->next = t->next->next;
    free(s);
}

void josephus(char ch, int m){
    node *t;
    int i;
    insert_nodes(ch);
    t = head;
    printf("\nAnswer :");
    while(t!=t->next){
        for(i=0; i<m-1; i++){
            t = t->next;
        }
        printf("\n%c", t->next->key);
        delete_after(t);
    }
    printf("\n%c",t->key);
}

void main(){
    char ch;
    int m;
    printf("Enter N and M :");
    scanf("%c %d",&ch, &m);
    josephus(ch,m);
}
