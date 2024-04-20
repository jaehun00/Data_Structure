# include <stdio.h>
# include <stdlib.h>

void average(int **matrix, int len)
{
    int sum = 0;
    int count = 0;
    int row, col;
    
    for(row=0; row<len; row++)
    {
        for(col=0; col<len; col++)
        {
            sum += *(*(matrix+row)+col);
            count ++;
        }
    }

    if (count > 0) {
        double average = (double)sum / count;
        printf("Average of the matrix: %.2f\n", average);
    } else {
        printf("Matrix is empty!\n");
    }
}

void main()
{
    int len, k;
    int row, col;

    printf("Input your square matrix size :");
    scanf("%d", &len);
    
    int **matrix = (int **)calloc(len,sizeof(int*));
    
    for (k=0 ; k < len ; k++)
    {
        *(matrix+k) = (int *)calloc(len, sizeof(int));
    }

    for(row = 0; row < len ; row++)
    {
        for(col = 0; col < len; col++)
        {
            printf("Enter (%d,%d):",row,col);
            scanf("%d", (*(matrix+row)+col));
        }
    }

    average(matrix, len);

    for (row = 0; row < len; row++) {
        free(*(matrix + row));
    }
    free(matrix);

}


