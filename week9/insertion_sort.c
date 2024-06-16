# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *, const void *);
void insert_sort(int *, int N);
void gen_insert_sort(void *, int nelem, int widht, FCMP fcmp);
void indirect_insert_sort(int *, int *, int N);

void main(){
    int number[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int index[SIZE];
    int i;

    indirect_insert_sort(number,index,SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d", number[index[i]]);
    }
    printf("\n");
}

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
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

void indirect_insert_sort(int *a, int *index, int N){
    int i, j, t;
    for(i=0; i<N; i++){
        index[i] = i;
    }
    for(i=0; i<N; i++){
        t = index[i];
        j = i;
        while(j>0 && a[index[j-1]]>a[t]){
            index[j] = index[j-1];
            j--;
        }
        index[j] = t;
    }
}
