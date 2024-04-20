# include <stdio.h>
# include <stdlib.h>

typedef struct _model{
    int val;
    float *color;
}model;

void main(){
    int k;
    model *object;

    object = (model *)calloc(5,sizeof(model));

    for(k = 0; k < 5; k++){
        (object+k)->color = (float *)calloc(3,sizeof(float));
    }
}