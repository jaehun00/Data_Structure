# include <stdio.h>
# include <stdlib.h>

typedef struct _complex
{
    float re;
    float im;
}CNum;

CNum multipy(CNum a, CNum b)
{
    CNum c;
    c.re = (a.re * b.re) - (a.im * b.im); // 실수부 계산
    c.im = (a.re * b.im) + (a.im * b.re); // 허수부 계산
    return c;
}

void main()
{
    CNum a = {1.3, 3.9};
    CNum b = {-3.3,8.4};
    CNum result;

    result = multipy(a,b);

    printf("%f %f\n", result.re, result.im);

}