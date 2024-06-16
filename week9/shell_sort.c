# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *, const void *);
void shell_sort(int *, int N);
void gen_shell_sort(void *, int nelem, int width, FCMP fcmp);

void main(){
    LARGE_INTEGER freq, start, stop;
    double diff;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int number[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int i;
    gen_shell_sort(number, SIZE, sizeof(int), intcmp);
    for(i=0; i<SIZE; i++){
        printf("%d", number[i]);
    }
    printf("\n");

    QueryPerformanceCounter(&stop);
    diff = (double)(stop.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("Time taken: %.6f seconds\n", diff);
}

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
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

void gen_shell_sort(void *base, int nelem, int width, FCMP fcmp){
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