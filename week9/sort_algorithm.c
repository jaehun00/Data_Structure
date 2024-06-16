# include <string.h>
# include "sorting.h"

void main(){
    int number[SIZE];
    int i;
    srand(time(0));
    generate_random_array(number, SIZE);

    int number_1[SIZE];
    memcpy(number_1, number, SIZE*sizeof(int));
    int number_2[SIZE];
    memcpy(number_2, number, SIZE*sizeof(int));
    int number_3[SIZE];
    memcpy(number_3, number, SIZE*sizeof(int));
    int number_4[SIZE];
    memcpy(number_4, number, SIZE*sizeof(int));

    LARGE_INTEGER freq, start;
    double diff;

    // Measure gen_bubble_sort
    start_timer(&start, &freq);
    gen_bubble_sort(number_1, SIZE, sizeof(int), intcmp);
    diff = stop_timer(start, freq);
    printf("gen_bubble_sort Time taken: %.6f seconds\n", diff);

    // Measure gen_select_sort
    start_timer(&start, &freq);
    gen_select_sort(number_2, SIZE, sizeof(int), intcmp);
    diff = stop_timer(start, freq);
    printf("gen_select_sort Time taken: %.6f seconds\n", diff);

    // Measure gen_insert_sort
    start_timer(&start, &freq);
    gen_insert_sort(number_3, SIZE, sizeof(int), intcmp);
    diff = stop_timer(start, freq);
    printf("gen_insert_sort Time taken: %.6f seconds\n", diff);
    
    // Measure gen_shell_sort
    start_timer(&start, &freq);
    gen_insert_sort(number_4, SIZE, sizeof(int), intcmp);
    diff = stop_timer(start, freq);
    printf("gen_shell_sort Time taken: %.6f seconds\n", diff);
}

void generate_random_array(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 100; // Change 100 to any range you prefer
    }
}
void start_timer(LARGE_INTEGER *start, LARGE_INTEGER *freq) {
    QueryPerformanceFrequency(freq);
    QueryPerformanceCounter(start);
}
double stop_timer(LARGE_INTEGER start, LARGE_INTEGER freq) {
    LARGE_INTEGER stop;
    QueryPerformanceCounter(&stop);
    return (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
}
int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
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