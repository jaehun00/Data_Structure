# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void read_file(int *, int, int, char *);
void median_filtering(void *, int, int, int(*fcmp)(const void *, const void *));
void noise_remove(int *, int *, int, int);

int intcmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void main(){
    int height = 44, width = 45;
    char filename[100] = "noisy_data.txt";

    int* input = (int*)calloc(height*width, sizeof(int));
    int* output = (int*)calloc(height*width, sizeof(int));

    read_file(input, height, width, filename);
    noise_remove(input, output, height, width);

    free(input);
    free(output);
}

void noise_remove(int *input, int *output, int height, int width){
    int x, y, xx, yy;
    FILE *fp;
    char filename[100] = "result.txt";
    int cnt;    
    int len = 2;
    // 5X5
    int *temp = (int*)calloc((2*len+1)*(2*len+1), sizeof(int));

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            cnt = 0;
            for(yy=y-len; yy<=y+len; yy++){
                for(xx=x-len; xx<=x+len; xx++){
                    if(xx<0 || yy<0 || xx>=width || yy>=height) break;
                    temp[cnt] = input[yy*width+xx];
                    cnt++;
                }
            }
            median_filtering(temp, cnt, sizeof(int), intcmp);
            output[y*width + x] = temp[cnt/2+1];
        }
    }
    free(temp);

    fp = fopen(filename, "w");

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            fprintf(fp, "%d\t", output[y*width+x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void median_filtering(void *base, int nelem, int width, int(*fcmp)(const void *, const void *)){
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

void read_file(int *input, int height, int width, char filename[])
{
    int x, y;
    FILE *fp;
    
    fp = fopen(filename, "r");

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            fscanf(fp, "%d", &input[y*width+x]);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
}
