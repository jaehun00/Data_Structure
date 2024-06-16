# include <string.h>
# include "sorting.h"

int bi_search(int key, int *, int N);

void main(){
    char str[20] = " TOSORTALGORITHM";
    int size = 15;
    int i;

    gen_heap_sort_bu(str, size, sizeof(char), charcmp);
    for(i=1; i<=size; i++) printf("%c",str[i]);

    char key = 'S';
    int p = gen_bii_search(&key, str, size, sizeof(char), charcmp);
    printf("\nFind your key at %d (value %c)\n", p, str[p]);

    char key2 = 'Z';
    p = gen_bi_insert(&key2, str, &size, sizeof(char), charcmp);
    printf("%s\n",str);

    char key3 = 'A';
    p = gen_bi_delete(&key3, str, &size, sizeof(char), charcmp);
    printf("%s\n",str);
}

int intcmp(const void *a, const void *b){
    return(*(int *)a - *(int *)b);
}

int charcmp(const void *a, const void *b){
    return(*(char *)a - *(char *)b);
}

int bi_search(int key, int *a, int N){
    int mid;
    int left=0;
    int right=N-1;
    while(right>=left){
        mid = (right + left)/2;
        if(key==a[mid]) return mid;
        if(key<a[mid]) right = mid - 1;
        else left = mid - 1;
    }
    return -1;
}

int bi_insert(int key, int *a, int *N){
    int p=0;
    int i;
    while(key>a[p] && p<*N) p++;
    for(i=*N; i>p; i--) a[i] = a[i-1];
    a[p] = key;
    (*N)++;

    return p;
}

int bi_delete(int key, int *a, int *N){
    int p;
    int i;
    if(*N>0){
        if(p=bi_search(key,a,*N) < 0) return -1;
        for(i=p+1; i<*N; i++) a[i-1] = a[i];
        (*N)--;
        
        return p;
    }
    return -1;
}

int gen_bi_search(void *key, void *base, int nelem, int width, FCMP fcmp){
    int mid;
    int left = 0;
    int right = nelem - 1;
    while(right >= left){
        mid = (right + left)/2;
        if(fcmp(key, BASE(mid)) == 0) return mid;
        if(fcmp(key, BASE(mid)) < 0) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int gen_bii_search(void *key, void *base, int nelem, int width, FCMP fcmp){
    int mid;
    int left = 0;
    int right = nelem-1;
    while(right>=left){
        mid = left + (float)(fcmp(key,BASE(left)))*(right-left)/(fcmp(BASE(right),BASE(left)));
        if(fcmp(key, BASE(mid)) == 0) return mid;
        if(fcmp(key, BASE(mid)) < 0) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int gen_bi_insert(void *key, void *base, int *nelem, int width, FCMP fcmp){
    int p = 0;
    int i;
    while(fcmp(key, BASE(p)) > 0 && p < *nelem) p++;
    for(i=*nelem; i>p; i--) memcpy(BASE(i), BASE(i-1), width);
    memcpy(BASE(p), key, width);
    (*nelem)++;
    return p;
}

int gen_bi_delete(void *key, void *base, int *nelem, int width, FCMP fcmp){
    int p;
    int i;
    if(*nelem > 0){
        if((p = gen_bii_search(key, base, *nelem, width, fcmp)) < 0) return -1;
        for(i=p+1; i<*nelem; i++) memcpy(BASE(i-1), BASE(i), width);
        (*nelem)--;
        return p;
    }
    return -1;
}

void gen_downheap(void *base, int nelem, int k, int width, FCMP fcmp){
    void *v;
    int i;
    v = malloc(width);
    memcpy(v, BASE(k), width);
    while(k<=nelem/2){
        i = k<<1;
        if(i<nelem && fcmp(BASE(i), BASE(i+1))<0) i++;
        if(fcmp(v, BASE(i)) >= 0) break;
        memcpy(BASE(k), BASE(i), width);
        k = i;
    }
    memcpy(BASE(k), v, width);
    free(v);
}

void gen_heap_sort_bu(void *base, int nelem, int width, FCMP fcmp){
    void *t;
    int k;

    t = malloc(width);

    for(k=nelem/2; k>=1; k--) gen_downheap(base, nelem, k, width, fcmp);

    while(nelem>1){
        memcpy(t, BASE(1), width);
        memcpy(BASE(1), BASE(nelem), width);
        memcpy(BASE(nelem), t, width);
        gen_downheap(base, --nelem, 1, width, fcmp);
    }

    free(t);
}