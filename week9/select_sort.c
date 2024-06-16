# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <Windows.h>

# define SIZE 10

typedef int (*FCMP)(const void *, const void *);

int intcmp(const void *, const void *);
void select_sort(int *, int N);
void gen_select_sort(void *, int nelem, int width, FCMP fcmp);

void main(){
    LARGE_INTEGER freq, start, stop;
    double diff;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    //////////////
    int number[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int i;

    gen_select_sort(number,SIZE,sizeof(int),intcmp);
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

void select_sort(int *a, int N){
    int min;
    int min_idx;
    int x, y;

    for(y=0; y<N-1; y++){
        min_idx = y;
        min = a[y];
        for(x=y+1; x<N; x++){
            if(min > a[x]){
                min = a[x];
                min_idx = x;
            }
        }
        a[min_idx] = a[y];
        a[y] = min;
    } 
}

void gen_select_sort(void *base, int nelem, int width, FCMP fcmp){
    void *min;
    int min_idx;
    int x, y;

    min = malloc(width);
    for(y = 0; y < nelem-1; y++){
        min_idx = y;
        memcpy(min, (char *)base + y*width, width);
        for(x = y+1; x < nelem; x++){
            if(fcmp(min, (char *)base + x*width) > 0){
                memcpy(min, (char *)base + x*width, width);
                min_idx = x;
            }
        }
        memcpy((char *)base + min_idx*width, (char *)base + y*width, width);
        memcpy((char *)base + y*width, min, width);
    }
    free(min);
}
