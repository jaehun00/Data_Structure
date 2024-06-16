# include <string.h>
# include "sorting.h"

# define SIZE 10

void main(){
    LARGE_INTEGER freq, start, stop;
    double diff;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int number[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int i;
    gen_quick_sort_stack(number, SIZE, sizeof(int), intcmp);
    for(i=0; i<SIZE; i++){
        printf("%d", number[i]);
    }
    printf("\n");

    QueryPerformanceCounter(&stop);
    diff = (double)(stop.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("Time taken: %.6f seconds\n", diff);
}

void init_stack(){
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

int push(int k){
    node *t;
    if((t = (node *)malloc(sizeof(node)))==NULL){
        printf("Out of memory !\n");
        return -1;
    }
    t->key = k;
    t->next = head->next;
    head->next = t;
    return k;
}

int pop(){
    node *t;
    int k;
    if(head->next==tail){
        printf("Stack underflow !\n");
        return -1;
    }
    t = head->next;
    k = t->key;
    head->next = t->next;
    free(t);

    return k;
}

int is_stack_empty(){
    if(head->next == tail){
        return -1;
    }
    return 0;
}

void print_stack(){
    node *t;
    t = head->next;
    while(t!=tail){
        printf("%-6d",t->key);
        t = t->next;
    }
}

void quick_sort_stack(int *a, int N){
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = N-1;
    push(r);
    push(l);
    while(!is_stack_empty()){
        l = pop();
        r = pop();
        if(r-l+1 > 1)
        {
            v = a[r];
            i = l-1;
            j = r;
            while(1){
                while(a[++i] < v);
                while(a[--j] > v);
                if(i >= j) break;
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
            t = a[i];
            a[i] = a[r];
            a[r] = t;
            push(r);
            push(i+1);
            push(i-1);
            push(l);
        }
    }
}

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}

void gen_quick_sort_stack(void *base, int nelem, int width, FCMP fcmp){
    void *v, *t;
    int i, j;
    int l, r;
    v = malloc(width);
    t = malloc(width);
    init_stack();
    l = 0;
    r = nelem-1;
    push(r);
    push(l);
    while(!is_stack_empty()){
        l = pop();
        r = pop();
        if(r-l+1 > 1)
        {
            memcpy(v,(char *)base + r*width, width);
            i = l-1;
            j = r;
            while(1){
                while(fcmp((char *)base + (++i)*width, v) < 0);
                while(fcmp((char *)base + (--j)*width, v) > 0);
                if(i >= j) break;
                memcpy(t, (char *)base + i*width, width);
                memcpy((char *)base + i*width, (char *)base + j*width, width);
                memcpy((char *)base + j*width, t, width);
            }
            memcpy(t, (char *)base + i*width, width);
            memcpy((char *)base + i*width, (char *)base + r*width, width);
            memcpy((char *)base + r*width, t, width);

            push(r);
            push(i+1);
            push(i-1);
            push(l);
        }
    }
    free(v);
    free(t);
}