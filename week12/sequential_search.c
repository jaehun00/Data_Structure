# include <string.h>
# include "sorting.h"

void main(){
    int number[MAX];
    int nitem = 10;

    int i;
    srand(time(0));
    generate_random_array(number, nitem);
    for(i=0; i<nitem; i++){
        printf("%d",number[i]);
        printf(" ");
    }
    printf("\n");
    int key = rand()%nitem;
    int t = seq_search(key, number, &nitem);
    printf("%d,%d\n", key, t);

    int key2 = rand()%nitem;
    t = seq_insert(key2, number, &nitem);
    for(i=0; i<nitem; i++){
        printf("%d",number[i]);
        printf(" ");
    }
    printf("\n");

    t = seq_delete(key2, number, &nitem);
    for(i=0; i<nitem; i++){
        printf("%d",number[i]);
        printf(" ");
    }
    printf("\n");
}

void generate_random_array(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 10; // Change 100 to any range you prefer
    }
}

int seq_search(int key, int *a, int *num){
    int i = 0;
    while(a[i] != key && i < *num) i++;

    return(i < *num ? i : -1);
}

int seq_f_search(int key, int *a, int *num){
    int p,i;
    if((p = seq_search(key, a, num)) < 0) return -1;
    for(i=p-1; i>=0; i--) a[i+1] = a[i];
    a[0] = key;

    return 0;
}

int seq_insert(int key, int *a, int *num){
    a[(*num)++] = key;
    
    return (*num)-1;
}

int seq_delete(int key, int *a, int *num){
    int p,i;
    if(*num > 0){
        if((p = seq_search(key, a, num)) < 0) return -1;
        for(i=p+1; i<*num; i++) a[i-1] = a[i];
        (*num)--;
        return p;
    }
    return -1;
}
