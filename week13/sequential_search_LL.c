# include <stdio.h>
# include <stdlib.h>
# include <windows.h>

typedef struct _node{ struct _node *next;} node;
typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}
int charcmp(const void *a, const void *b){
    return (*(char *)a- *(char *)b);
}

void init_list(node **);
void *llv_search(void *, node *, int *, int width, FCMP fcmp, int *);
void *llv_insert(void *, node *, int *, int width, FCMP fcmp);
void *llv_delete(void *, node *, int *, int width, FCMP fcmp);
void *llfv_search(void *, node *, int *, int width, FCMP fcmp);
void read_file(char **, int *, char filename[]);
void print_list(node *);

# define LEN 5
# define MAX 100
# define SEQ 15

void main(){
    char *data[MAX], key;
    int len, size, pos;
    void *p;
    node *t, *head;
    int i;

    for(i=0; i<MAX; i++){
        data[i] = (char *)malloc(SEQ * sizeof(char));
    }
    
    len = 0;
    read_file(data, &len, "./week13/words.txt");
    init_list(&t);
    head = t;

    size = 0;
    for(i=0; i<len; i++){
        t = llv_insert(data[i], t, &size, sizeof(char)*SEQ, charcmp);
    }
    
    print_list(head);

    key = 'k', pos = -1;
    t = head;
    while(1){
        p = llv_search(&key, t, &size, sizeof(char), charcmp, &pos);
        if(p==NULL) break;

        printf("index: %d, value: %s \n", pos, (node *)p);
        t = (node *)p - 1;
    }
    
    for(i=0; i<MAX; i++) free(data[i]);
}

void print_list(node *base){
    int i;
    node *t;
    t = base->next;

    while(t != NULL){
        printf("%s\n", (char *)(t+1));
        t = t->next;
    }
    printf("\n");
}

void read_file(char *data[], int *len, char filename[]){
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp==NULL) return;
    while(fscanf(fp, "%s\n", data[*len]) != EOF){
        (*len)++;
        if (*len >= MAX) break;
    }

    fclose(fp);
}

void init_list(node **p){
    *p = (node *)malloc(sizeof(node));
    (*p)->next = NULL;
}

void *llv_insert(void *key, node *base, int *num, int width, FCMP fcmp){
    node *t;
    t = (node *)malloc(sizeof(node) + width);
    memcpy(t+1, key, width);
    t->next = base->next;
    base->next = t;
    (*num)++;
    return t;
}

void *llv_delete(void *key, node *base, int *num, int width, FCMP fcmp){
    node *t, *p;

    p = base;
    t = base->next;
    while(t != NULL && fcmp(t+1, key) != 0){
        p = t;
        t = t->next;
    }
    if(t==NULL) return NULL;

    p->next = t->next;
    free(t);

    (*num)--;

    return p;
}

void *llv_search(void *key, node *base, int *num, int width, FCMP fcmp, int *pos){
    node *t;
    t = base->next;
    (*pos)++;
    while(fcmp(t+1,key) != 0 && t != NULL){
        t = t->next;
        (*pos)++;
    }
    return (t == NULL ? NULL : t+1);
}

