#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
int *add(int x, int y);
void sub(int *x, int n);
int function_A(int N);

void main()
{
    int a = 100, b = 200;
    printf("a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);

    int *result;
    result = add(5,9);
    printf("result = %d", *result);

    int c[3] = {1, 2, 3};
    sub(c, 3);
    printf("%d %d %d \n",c[0], c[1], c[2]);
    
    int (*fptr) (int);
    fptr = function_A;
    printf("%d\n", function_A(100));
    printf("%d\n", fptr(100));
}

void swap(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int *add(int x, int y)
{
    int *z = (int *)malloc(sizeof(int));
    *z = x + y;
    return z;
}

void sub(int *x, int n)
{
    int j;
    for(j=0; j<n; j++)
    {
        *(x+j) -= 1;
    }
}

int function_A(int N)
{
    int a;
    for(a=0; N>0; N--)
        a += N;
    return a;
}