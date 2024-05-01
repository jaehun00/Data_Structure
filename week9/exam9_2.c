# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

void insert_sort(int *a, int N){
    int i, j, t;
    for(i=1; i<N; i++){
        t = a[i];
        j = i;
        while(j>0 && a[j-1]>t){
            a[j] = a[j-1];
            j--;
        }
        a[j] = t;
    }
}

void indirect_insert_sort(int *a, int *index, int N){
    int i, j, t;
    for(i=0; i<N; i++){
        index[i] = i;
    }
    for(i=0; i<N; i++){
        t = index[i];
        j = i;
        while(j>0 && a[index[j-1]]>a[t]){
            index[j] = index[j-1];
            j--;
        }
        index[j] = i;
    }
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
void main(){
    int N = 4;
    int i;
    
    int a[4] = {1,5,6,3};
    int index[4];
    indirect_insert_sort(a,index,N);
    for(i=0;i<N;i++){
        printf("%d", a[index[i]]);
    }
    printf("\n");

    int b[4] = {1,5,6,3};
    shell_sort(b,N);
    for(i=0;i<N;i++){
        printf("%d", b[i]);
    }
    printf("\n");
}