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
    // 함수 포인터 선언
    int (*fptr)(int, int);
    
    // add 함수를 가리키도록 설정
    fptr = add;
    result = fptr(10, 20);
    printf("Result of addition: %d\n", result);

    // sub 함수를 가리키도록 설정
    fptr = sub;
    result = fptr(30, 15);
    printf("Result of subtraction: %d\n", result);

}