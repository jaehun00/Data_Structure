# include <stdio.h>
# include <stdlib.h>
# include <time.h>

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

void main(){
    int a[4] = {1,5,6,3};
    int N = 4;
    gen_select_sort(a,N,sizeof(int),intcmp);
    int i;
    for(i=0;i<N;i++){
        printf("%d", a[i]);
    }

}
