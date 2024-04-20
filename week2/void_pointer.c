#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(void *a, void *b, int n)
{
    void *t;
    t = malloc(n);
    memcpy(t, a, n);
    memcpy(a, b, n);
    memcpy(b, t, n);
    free(t);
}

void main()
{
    char c1 = 'A', c2 = 'B';
    int i1 = 3, i2 = 9;
    float f1 = 3.3, f2 = 9.9;

    swap(&c1, &c2, sizeof(char));
    swap(&i1, &i2, sizeof(int));
    swap(&f1, &f2, sizeof(float));

    printf("%c, %c\n", c1, c2);
    printf("%d, %d\n", i1, i2);
    printf("%f, %f\n", f1, f2);
}