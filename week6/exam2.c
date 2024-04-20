#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX 10

int queue[MAX];
int front, rear;

void init_queue()
{
    front = 0;
    rear = 0;
}

void clear_queue()
{
    front = rear;
}

int put(int k)
{
    if((rear+1) % MAX == front)
    {
        printf("Queue overflow!\n");
        return -1;
    }
    queue[rear] = k;
    rear = ++rear%MAX;
    return k;
}

void print_queue()
{
    int k;
    for(k=front; k!=rear; k=++k%MAX)
        printf("%-6d",queue[k]);
}
void main()
{
    int k;
    init_queue();
    put(3);
    print_queue();

}