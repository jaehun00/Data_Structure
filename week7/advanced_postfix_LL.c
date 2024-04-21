# include <stdio.h>
# include <stdlib.h>

typedef struct _node{
    int key;
    struct _node *next;
}node;

node *head, *tail;

void init_stack(){
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

int push(int k){
    node *t;
    if((t=(node *)malloc(sizeof(node)))==NULL){
        printf("Overflow memory");
        return -1;
    }
    t->key = k;
    t->next = head->next;
    head->next = t;
    return 1;
}

int pop(){
    node *t;
    int k;
    if(head->next == tail){
        printf("Underflow memory");
        return -1;
    }
    t = head->next;
    k = t->key;
    head->next = t->next;
    free(t);
    
    return k;
}

void clear(){
    node *t, *s;
    t = head->next;
    while(t!=tail){
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
}

int get_stack_top(){
    node *t;
    int k;
    t = head->next;
    if(t==tail){
        return -1;
    }
    k = t->key;
    return k;
}

int is_op(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

int is_stack_empty(){
    if(head->next == tail){
        return -1;
    }
    return 0;
}

int precedence(int op){
    if(op == '(') return 0;
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    else return 3;
}

void postfix(char *dst, char *src){
    init_stack();
    while(*src){
        if(*src=='('){
            push(*src);
            src++;
        }
        else if(*src==')'){
            while(get_stack_top() != '('){
                *dst++ = pop();
                *dst++ = ' ';
            }
            pop();
            src++;
        }
        else if(is_op(*src)){
            while(!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src)){
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src);
            src++;
        }
        else if(*src >= '0' && *src <= '9'){
            do{
                *dst++ = *src++;
            }while(*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else
            src++;
    }
    while(!is_stack_empty()){
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

int calc_postfix(char *src){
    clear();
    init_stack();
    while(*src){
        if(*src >= '0' && *src <= '9'){
            int i = *src - '0';
            push(i);
            src++;
        }
        else if(*src > '9'){
            int i = atoi(src);
            push(i);
            src++;
        }
        else if(is_op(*src)){
            int op2 = pop();
            int op1 = pop();
            switch(*src){
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
            src++;
        }
        else
            src++;
    }
    return pop();
}

void main()
{
    char exp[256];
    char src[256] = "(1*(2+3/4)+5)/6+7";

    postfix(exp, src);
    printf("Postfix representation : %s\n", exp);

    int result = calc_postfix(exp);
    printf("Postfix result : %d\n", result);
}