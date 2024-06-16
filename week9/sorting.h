# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10000
typedef struct _node{
    int key;
    struct _node *next;
}node;

node *head, *tail;

typedef int (*FCMP)(const void *, const void *);

void generate_random_array(int *, int size);
void start_timer(LARGE_INTEGER *start, LARGE_INTEGER *freq);
double stop_timer(LARGE_INTEGER start, LARGE_INTEGER freq);

int intcmp(const void *, const void *);
void bubble_sort(int *, int N);
void insert_sort(int *, int N);
void indirect_insert_sort(int *, int *, int N);
void select_sort(int *, int N);
void shell_sort(int *, int N);
void gen_bubble_sort(void *, int nelem, int width, FCMP fcmp);
void gen_insert_sort(void *, int nelem, int widht, FCMP fcmp);
void gen_select_sort(void *, int nelem, int width, FCMP fcmp);
void gen_shell_sort(void *, int nelem, int width, FCMP fcmp);
