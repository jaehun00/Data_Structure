# include <string.h>
# include "sorting.h"

void main(){
    int number[SIZE+1];
    int i;
    srand(time(0));
    generate_random_array(number, SIZE);

    LARGE_INTEGER freq, start;
    double diff;

    // Measure gen_select_sort
    start_timer(&start, &freq);
    gen_heap_sort_td(number, SIZE, sizeof(int), intcmp);
    for(i=1; i<=SIZE; i++){
        printf("%d", number[i]);
        printf(" ");
    }
    printf("\n");
    diff = stop_timer(start, freq);
    printf("gen_select_sort Time taken: %.6f seconds\n", diff);

}

void generate_random_array(int *arr, int size) {
    int i;
    for (i = 1; i <= size; i++) {
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

void gen_upheap(void *base, int k, int width, FCMP fcmp){
    void *v;
    void *max_val; 
    max_val = malloc(width);
    v = malloc(width);
    memcpy(v, (char *)base + k*width, width);
    memset(max_val, 0xFF, width); // assuming this sets it to a value larger than any valid element

    memcpy((char *)base, max_val, width);
    while(k>1 && fcmp((char *)base + (k/2)*width, v) < 0){
        memcpy((char *)base + k*width, (char *)base + (k/2)*width, width);
        k /= 2;
    }
    memcpy((char *)base + k*width, v, width);
    free(v);
    free(max_val);
}

void gen_downheap(void *base, int nelem, int k, int width, FCMP fcmp){
    void *v;
    int i;
    v = malloc(width);
    memcpy(v, (char *)base + k*width, width);
    while(k<=nelem/2){
        i = k<<1;
        if(i<nelem && fcmp((char *)base + i*width, (char *)base + (i+1)*width)<0) i++;
        if(fcmp(v, (char *)base + i*width) >= 0) break;
        memcpy((char *)base + k*width, (char *)base + i*width, width);
        k = i;
    }
    memcpy((char *)base + k*width, v, width);
    free(v);
}

void gen_insert(void *base, int *nelem, void *v, int width, FCMP fcmp){
    memcpy((char *)base + (++(*nelem))*width, v, width);
    gen_upheap(base, *nelem, width, fcmp);
}

void *gen_extract(void *base, int *nelem, int width, FCMP fcmp){
    void *v;
    v = malloc(width);
    memcpy(v, (char *)base + 1*width, width);
    memcpy((char *)base + 1*width, (char *)base + ((*nelem)--)*width, width);
    gen_downheap(base, *nelem, 1, width, fcmp);
    return v;
}

void gen_heap_sort_td(void *base, int nelem, int width, FCMP fcmp){
    int i;
    int hn = 0;

    for(i=1; i<=nelem; i++) gen_insert(base, &hn, (char *)base + i*width, width, fcmp);
    for(i=hn; i>=1; i--){
        void *v = gen_extract(base, &hn, width, fcmp);
        memcpy((char *)base + i*width, v, width);
        free(v);
    }
}

void gen_heap_sort_bu(void *base, int nelem, int width, FCMP fcmp){
    void *t;
    int k;

    t = malloc(width);

    for(k=nelem/2; k>=1; k--) gen_downheap(base, nelem, k, width, fcmp);

    while(nelem>1){
        memcpy(t, (char *)base + 1*width, width);
        memcpy((char *)base + 1*width, (char *)base + nelem*width, width);
        memcpy((char *)base + nelem*width, t, width);
        gen_downheap(base, --nelem, 1, width, fcmp);
    }

    free(t);
}