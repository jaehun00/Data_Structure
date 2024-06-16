# include <string.h>
# include "sorting.h"

# define SIZE 20

void main(){
    int number[SIZE];
    int i;
    srand(time(0));
    generate_random_array(number, SIZE);

    LARGE_INTEGER freq, start, stop;
    double diff;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    gen_random_quick_sort(number, SIZE, sizeof(int), intcmp);

    QueryPerformanceCounter(&stop);
    diff = (double)(stop.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("Time taken: %.6f seconds\n", diff);
}

// Function to generate a random array
void generate_random_array(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 100; // Change 100 to any range you prefer
    }
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

void insert_sort(int *a, int N){
    int i, j, t;
    for(i=1; i<N; i++){
        t = a[i];
        j = i;
        while(j>0 && a[j-1]>t){
            a[j] = a[j-1];
            j--;
        }
        a[j] = t;
    }
}

void random_quick_sort(int *a, int N){
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
        if(r-l+1 > 200)
        {
            t = rand()%N;
            v = a[t];
            a[t] = a[r];
            a[r] = v;
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
        else insert_sort(a+l, r-l+1);
    }
}

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}

void gen_insert_sort(void *base, int nelem, int width, FCMP fcmp){
    void *t;
    int i, j;

    t = malloc(width);
    for(i=0; i < nelem; i++){
        j = i;
        memcpy(t, (char *)base + i*width, width);
        while(j>0 && fcmp((char *)base + (j-1)*width, t) > 0){
            memcpy((char *)base + j*width, (char *)base + (j-1)*width, width);
            j--;
        }
        memcpy((char *)base + j*width, t, width);
    }
    free(t);
}
void gen_random_quick_sort(void *base, int nelem, int width, FCMP fcmp){
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
        if(r-l+1 > 200)
        {
            i = rand()%nelem;
            memcpy(v, (char *)base + i*width, width);
            memcpy((char *)base + i*width, (char *)base + r*width, width);
            memcpy((char *)base + r*width, v, width);
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
        else gen_insert_sort((char *)base + l, r-l+1, width, fcmp);
    }
    free(v);
    free(t);
}