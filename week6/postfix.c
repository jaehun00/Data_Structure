#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    int key;
    struct _node *next;
}node;

node *head, *tail;

void init_stack()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

int push(int k)
{
    node *t;
    if((t = (node *)malloc(sizeof(node))) == NULL)
    {
        printf("Out of memory !\n");
        return -1;
    }
    t->key = k;
    t->next = head->next;
    head->next = t;

    return k;
}

int pop()
{
    node *t;
    int k;
    if(head->next == tail)
    {
        printf("Stack underflow !\n");
        return -1;
    }
    t = head->next;
    k = t->key;
    head->next = t->next;
    free(t);

    return k;
}

void clear()
{
    node *t, *s;
    t = head->next;

    while(t != tail)
    {
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
}

void print_stack()
{
    node *t;
    t = head->next;
    while(t != tail)
    {
        printf("%-6d", t->key); //Æø
        t = t->next;
    }
}

// dst <= want to print
// src <= Input source
void postfix(char *dst, char *src)
{
    char c;
    init_stack();
    while(*src){
        // stage 4 : if meet ")" pop
        if(*src == ')'){
            *dst++ = pop();
            *dst = ' ';
            src++;
        }
        // stage 3 : if meet operator push
        else if(*src == '+' || *src == '-' || *src == '*' || *src == '/'){
            push(*src);
            src++;
        }
        // stage 2 : if meet num put in dst
        else if(*src >= '0' && *src <= '9'){
            do{
                *dst++ = *src++;
            }while(*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else
            src++;
    }
    *dst = 0;
}

int calc_postfix(char *exp){
    char token;
    int i, op1, op2;
    clear();
    init_stack();
    while(*exp){
        if(*exp >= '0' && *exp <= '9'){
            do{
                i = *exp -'0';
                push(i);
                exp++;
            }while(*exp >= '0' && *exp <= '9');
        }
        else if(*exp == '+' || *exp == '-' || *exp == '*' || *exp == '/'){
            op2 = pop();
            op1 = pop();
            switch (*exp)
            {
                case '+':
                    push((op1+op2));
                    break;
                case '-':
                    push((op1-op2));
                    break;
                case '*':
                    push((op1*op2));
                    break;
                case '/':
                    push((op1/op2));
                    break;
            }
            exp++;
        }
        else
            exp++;
    }
    return pop();
}

void main()
{
    char exp[256];
    char src[256] = "(1+(2*3))";

    postfix(exp, src);
    printf("Postfix representation : %s\n", exp);

    int result = calc_postfix(exp);
    printf("Postfix result : %d\n",result);
}