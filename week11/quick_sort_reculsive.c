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
    gen_quick_sort(number, SIZE, sizeof(int), intcmp);
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

void quick_sort(int *a, int N){
    int v, t; //pivot, temp
    int i, j; //right, left
    if(N>1) // Termination
    {
        v = a[N-1]; //pivot
        i = -1; // for ++i start with 0
        j = N-1; // for --j start with N-2
        while(1){
            while(a[++i]<v); // if a[i]>v stop
            while(a[--j]>v); // if a[j]<v stop
            if(i>=j) break;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        // if i >= j
        t = a[i];
        a[i] = a[N-1];
        a[N-1] = t;

        // reculsve
        quick_sort(a, i);
        quick_sort(a+i+1, N-i-1);
    }
}

void gen_quick_sort(void *base, int nelem, int width, FCMP fcmp){
    void *v, *t;
    int i, j;
    v = malloc(width);
    t = malloc(width);
    if(nelem>1){
        memcpy(v, (char *)base + (nelem-1)*width, width);
        i = -1;
        j = nelem-1;
        while(1){
            while(fcmp((char *)base + (++i)*width, v) < 0);
            while(fcmp((char *)base + (--j)*width, v) > 0);
            if(i>=j) break;
            memcpy(t, (char *)base + i*width, width);
            memcpy((char *)base + i*width, (char *)base + j*width, width);
            memcpy((char *)base + j*width, t, width);
        }
        memcpy(t, (char *)base + i*width, width);
        memcpy((char *)base + i*width, (char *)base + (nelem-1)*width, width);
        memcpy((char *)base + (nelem-1)*width, t, width);
        
        gen_quick_sort(base, i, width, fcmp);
        gen_quick_sort((char *)base+(i+1), nelem-i-1, width, fcmp);
    }
    free(v);
    free(t);
}