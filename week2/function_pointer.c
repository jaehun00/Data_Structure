#include <stdio.h>

int add(int x, int y)
{
    int result;
    result = x + y;
    return result;
}

int sub(int x, int y)
{
    int result;
    result = x - y;
    return result;
}

void main()
{
    int result;
    // �Լ� ������ ����
    int (*fptr)(int, int);
    
    // add �Լ��� ����Ű���� ����
    fptr = add;
    result = fptr(10, 20);
    printf("Result of addition: %d\n", result);

    // sub �Լ��� ����Ű���� ����
    fptr = sub;
    result = fptr(30, 15);
    printf("Result of subtraction: %d\n", result);

}