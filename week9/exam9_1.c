# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

# define SIZE 10

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

int intcmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void gen_select_sort(void *base, int nelem, int width, int(*fcmp)(const void *, const void *)){
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

void gen_bubble_sort(void *base, int nelem, int width, int(*fcmp)(const void *, const void *)){
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

void main(){
    int number1[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    int i;

    gen_select_sort(number1,SIZE,sizeof(int),intcmp);
    for(i=0;i<SIZE;i++){
        printf("%d", number1[i]);
    }
    printf("\n");

    int number2[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    bubble_sort(number2, SIZE);
    for(i=0;i<SIZE;i++){
        printf("%d", number2[i]);
    }
    printf("\n");

    int number3[SIZE] = {9, 0, 1, 5, 8, 3, 6, 7, 2, 4};
    gen_bubble_sort(number3,SIZE,sizeof(int),intcmp);
    for(i=0;i<SIZE;i++){
        printf("%d", number3[i]);
    }
    printf("\n");
}


