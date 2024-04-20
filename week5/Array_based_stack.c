#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 10

int stack[MAX];
int top;

void init_stack(void)
{
    top = -1;
}

int push(int t)
{
    if(top >= MAX-1)
    {
        printf("Stack overflow !!!\n");
        return -1;
    }
    stack[++top] = t;
    return t;
}

int pop()
{
    if(top < 0)
    {
        printf("Stack underflow !!!\n");
        return -1;
    }
    return stack[top--];
}

void print_stack()
{
    int i;
    for (i=top; i>=0; i--)
    {
        printf("%-6d\n",stack[i]);
    }
}

void main()
{
    int k;
    init_stack();

    push(3);
    push(6);
    push(9);
    push(1);
    push(6);
    push(3);

    push(4);

    init_stack();

    pop();
    print_stack();

}
