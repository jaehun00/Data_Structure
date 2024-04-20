#include <stdio.h>

void main()
{
    FILE *fp;
    int score;
    int num = 0;
    float avg = 0.0;

    fp = fopen("./week2/score.txt","w");

    while(1)
    {
        if(score==0)
            break;
        printf("Input score:");
        scanf("%d",&score);
        fprintf(fp, "%d\n", score);
    }
    fclose(fp);
    
    if((fp = fopen("./week2/score.txt","r")) != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%d", &score);
            avg += score;
            printf("%d\n",score);
            num++;
        }
        avg /= (float)num;
        printf("average = %f\n", avg);
    }

}