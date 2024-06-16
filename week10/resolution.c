# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void read_file(float *, int, int, char *);
void median_filtering(void *, int, int, int(*fcmp)(const void *, const void *));
void noise_remove(float *, float *, int, int);

int intcmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

void main(){
    int height = 44, width = 45;
    char filename[100] = "noisy_data.txt";

    float* input = (float*)calloc(height*width, sizeof(float));
    float* output = (float*)calloc(height*width, sizeof(float));

    read_file(input, height, width, filename);
    noise_remove(input, output, height, width);

    free(input);
    free(output);
}

void noise_remove(float *input, float *output, int height, int width){
    int x, y, xx, yy;
    FILE *fp;
    char filename[100] = "result.txt";
    int cnt;    
    int len = 2;
    // 5X5
    float *temp = (float*)calloc((2*len+1)*(2*len+1), sizeof(float));

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){

            cnt = 0;
            for(yy=y-len; yy<=y+len; yy++){
                for(xx=x-len; xx<=x+len; xx++){
                    temp[cnt] = input[yy*(2*len+1)+xx];
                    cnt++;
                }
            }
            median_filtering(temp, cnt, sizeof(float), intcmp);
            output[y*width + x] = temp[cnt%2];
        }
    }

    fp = fopen(filename, "w");

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            fprintf(fp, "%.2f", &output[y*width+x]);
            fprintf(fp, " ");
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

void read_file(float *input, int height, int width, char filename[])
{
    int x, y;
    FILE *fp;
    
    fp = fopen(filename, "r");

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            fscanf(fp, "%f", &input[y*width+x]);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
}
