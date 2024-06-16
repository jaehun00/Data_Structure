# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10
# define MAX 100
# define INT_MAX 1000
# define BASE(i) ((char *)base + (i)*width)

typedef struct _node{
    int key;
    struct _node *next;
}node;

node *head, *tail;

typedef struct _card{
    int no;
    char name[20];
}card;

typedef int (*FCMP)(const void *, const void *);

void generate_random_array(int *, int size);
void start_timer(LARGE_INTEGER *start, LARGE_INTEGER *freq);
double stop_timer(LARGE_INTEGER start, LARGE_INTEGER freq);
int intcmp(const void *, const void *);
int charcmp(const void *, const void *);
int cardcmp(const void *, const void *);
void init_stack();
int push(int k);
int pop();
int is_stack_empty();
void print_stack();

void bubble_sort(int *, int N);
void insert_sort(int *, int N);
void indirect_insert_sort(int *, int *, int N);
void select_sort(int *, int N);
void shell_sort(int *, int N);

void gen_bubble_sort(void *, int nelem, int width, FCMP fcmp);
void gen_insert_sort(void *, int nelem, int widht, FCMP fcmp);
void gen_select_sort(void *, int nelem, int width, FCMP fcmp);
void gen_shell_sort(void *, int nelem, int width, FCMP fcmp);

// algorithm2
void quick_sort(int *, int N);
void quick_sort_stack(int *, int N);
void random_quick_sort(int *, int N);

void downheap(int *, int N, int k);
void insert(int *, int *, int v);
int extract(int *, int *);
void heap_sort_td(int *, int N);
void heap_sort_bu(int *, int N);

void gen_quick_sort(void *, int nelem, int width, FCMP fcmp);
void gen_quick_sort_stack(void *, int nelem, int width, FCMP fcmp);
void gen_insert_sort(void *, int nelem, int width, FCMP fcmp);
void gen_random_quick_sort(void *, int nelem, int width, FCMP fcmp);

void gen_upheap(void *, int k, int width, FCMP fcmp);
void gen_downheap(void *, int nelem, int k, int width, FCMP fcmp);
void gen_insert(void *, int *, void *, int width, FCMP fcmp);
void *gen_extract(void *, int *, int width, FCMP fcmp);
void gen_heap_sort_td(void *, int nelem, int width, FCMP fcmp);
void gen_heap_sort_bu(void *, int nelem, int width, FCMP fcmp);

//Binary Search
int gen_bi_search(void *, void *, int nelem, int width, FCMP fcmp);
int gen_bi_insert(void *, void *, int *, int width, FCMP fcmp);
int gen_bi_delete(void *, void *, int *, int width, FCMP fcmp);
int gen_bii_search(void *, void *, int nelem, int width, FCMP fcmp);

//Sequential Search
int seq_search(int key, int *, int *);
int seq_f_search(int key, int *, int *);
int seq_insert(int key, int *, int *);
int seq_delete(int key, int *, int *);

//id card
int lv_search(void *, void *, int *, int width, FCMP fcmp);
int lv_delete(void *, void *, int *, int width, FCMP fcmp);
int lv_insert(void *, void *, int *, int width, FCMP fcmp);
int lfv_search(void *, void *, int *, int width, FCMP fcmp);