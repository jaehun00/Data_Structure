# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *, const void *);
void bubble_sort(int *, int N);
void gen_bubble_sort(void *, int nelem, int width, FCMP fcmp);

void main(){
    LARGE_INTEGER freq, start, stop;
    double diff;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    //////////////
    int number[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int i;
    
    gen_bubble_sort(number,SIZE,sizeof(int),intcmp);
    for(i=0;i<SIZE;i++){
        printf("%d", number[i]);
    }
    printf("\n");
    ///////////////

    QueryPerformanceCounter(&stop);
    diff = (double)(stop.QuadPart - start.QuadPart)/freq.QuadPart;
    printf("Time taken: %.6f seconds\n", diff);
}

int intcmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void bubble_sort(int *a, int N){
    int i, j, t;

    for(i=0; i<N-1; i++){
        for(j=1; j<N-i; j++){
            if(a[j-1] > a[j]){
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }
}

void gen_bubble_sort(void *base, int nelem, int width, FCMP fcmp){
    void *t;
    int i, j;

    t = malloc(width);
    for(i = 0; i < nelem-1; i++){
        for(j = 1; j < nelem-i; j++){
            if(fcmp((char *)base + (j-1)*width, (char *)base + j*width) > 0){
                memcpy(t, (char *)base + (j-1)*width, width);
                memcpy((char *)base + (j-1)*width, (char*)base + j*width, width);
                memcpy((char *)base + j*width, t, width);
            }
        }
    }
    free(t);
}
