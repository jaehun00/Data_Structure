# include <string.h>
# include "sorting.h"

void main(){
    int number[SIZE+1];
    int i;
    srand(time(0));
    generate_random_array(number, SIZE);

    heap_sort_bu(number, SIZE);
    for(i=1; i<=SIZE; i++){
        printf("%d", number[i]);
        printf(" ");
    }
    printf("\n");
}

void generate_random_array(int *arr, int size) {
    int i;
    for (i = 1; i <= size; i++) {
        arr[i] = rand() % 100; // Change 100 to any range you prefer
    }
}

void upheap(int *a, int k){
    int v;
    v = a[k];
    a[0] = INT_MAX;
    while(a[k/2] <= v){
        a[k] = a[k/2];
        k /= 2;
    }
    a[k] = v;
}

void downheap(int *a, int N, int k){
    int i, v;
    v = a[k];
    while(k<=N/2){
        i = k<<1;
        if(i<N && a[i]<a[i+1]) i++;
        if(v>=a[i]) break;
        a[k] = a[i];
        k = i;
    }
    a[k] = v;
}

void insert(int *a, int *N, int v){
    a[++(*N)] = v;
    upheap(a, *N);
}

int extract(int *a, int *N){
    int v = a[1];
    a[1] = a[(*N)--];
    downheap(a, *N, 1);

    return v;
}

void heap_sort_td(int *a, int N){
    int i;
    int hn = 0;
    for(i=1; i<=N; i++) insert(a, &hn, a[i]);
    for(i=hn; i>=1; i--){
        a[i] = extract(a, &hn);
    }
}

void heap_sort_bu(int *a, int N){
    int k, t;

    for(k=N/2; k>=1; k--) downheap(a, N, k);

    while(N>1){
        t = a[1];
        a[1] = a[N];
        a[N] = t;
        downheap(a,--N,1);
    }
}