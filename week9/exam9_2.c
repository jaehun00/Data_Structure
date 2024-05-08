# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

#define SIZE 4

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

void gen_insert_sort(void *base, int nelem, int width, int(*fcmp)(const void *, const void *)){
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
        a[index[j]] = a[t];
    }
}

void shell_sort(int *a, int N){
    int i, j, k, h, v;
    for(h=N/2; h>0; h/=2){
        for(i=0; i<h; i++){
            for(j=i+h; j<N; j+=h){
                v = a[j];
                k = j;
                while(k>h-1 && a[k-h]>v){
                    a[k] = a[k-h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }
}

void gen_shell_sort(void *base, int nelem, int width, int(*fcmp)(const void *, const void *)){
    int i, j, k, h;
    void *v;
    v = malloc(width);

    for(h=nelem/2; h>0; h/=2){
        for(i=0; i<h; i++){
            for(j=i+h; j<nelem; j+=h){
                memcpy(v, (char *)base + j*width, width);
                k = j;
                while(k>h-1 && fcmp((char *)base + (k-h)*width, v) > 0){
                    memcpy((char *)base + k*width, (char *)base + (k-h)*width, width);
                    k -= h;
                }
                memcpy((char *)base + k*width, v, width);
            }
        }
    }
    free(v);
}
void main(){
    int i;
    
    int a[SIZE] = {1,5,6,3};
    int index[SIZE];
    indirect_insert_sort(a,index,SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d", a[index[i]]);
    }
    printf("\n");

    int b[SIZE] = {1,5,6,3};
    shell_sort(b,SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d", b[i]);
    }
    printf("\n");

    int c[SIZE] = {1,5,6,3};
    gen_insert_sort(c, SIZE, sizeof(int), intcmp);
    for(i=0; i<SIZE; i++){
        printf("%d", c[i]);
    }
    printf("\n");

    int d[SIZE] = {1,5,6,3};
    gen_shell_sort(d, SIZE, sizeof(int), intcmp);
    for(i=0; i<SIZE; i++){
        printf("%d", d[i]);
    }
    printf("\n");
}