#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int key;
    struct _node *left;
    struct _node *right;
}node;

typedef struct _queue
{
    node *data;
    struct _queue *prev;
    struct _queue *next;
}queue;

queue *q_head, *q_tail;
node *head, *tail;

void init_tree()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}

void init_queue()
{
    q_head = (queue *)calloc(1, sizeof(queue));
    q_tail = (queue *)calloc(1, sizeof(queue));
    q_head->next = q_tail;
    q_head->prev = q_head;
    q_tail->next = q_tail;
    q_tail->prev = q_head;
}

void visit(node *t){
    printf("%c", t->key);
}

void preorder_traverse(node *t){
    if(t!=tail) {
        visit(t);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void inorder_traverse(node *t){
    if(t!=tail){
        inorder_traverse(t->left);
        visit(t);
        inorder_traverse(t->right);
    }
}

void postorder_traverse(node *t){
    if(t!=tail){
        postorder_traverse(t->left);
        postorder_traverse(t->right);
        visit(t);
    }
}

node *put(node *data){
    queue *t;
    if((t=(queue *)malloc(sizeof(queue)))==NULL){
        return NULL;
    }
    t->data = data;
    q_tail->prev->next = t;
    t->prev = q_tail->prev;
    q_tail->prev = t;
    t->next = q_tail;

    return data;
}

node *get(){
    node *data;
    queue *t;
    t = q_head->next;
    if(t==q_tail){
        return NULL;
    }
    data = t->data;
    q_head->next = t->next;
    t->next->prev = q_head;
    free(t);
    return data;
}

int is_queue_empty(){
    if(q_head->next == q_tail){
        return 1;
    }
    return 0;
}

void levelorder_traverse(node *t){
    put(t);
    while(!is_queue_empty()){
        t = get();
        visit(t);

        if(t->left!=tail)
            put(t->left);
        if(t->right!=tail)
            put(t->right);
    }
}

node *create_node(char ch){
    node *t;
    t = (node *)calloc(1, sizeof(node));
    t->key = ch;
    return t;
}

void main() {
    // Initialize the tree
    init_tree();
    init_queue();
    // Create nodes for the tree
    node *A = create_node('A');
    node *B = create_node('B');
    node *C = create_node('C');
    node *D = create_node('D');
    node *E = create_node('E');
    node *F = create_node('F');
    node *G = create_node('G');
    node *H = create_node('H');
    node *I = create_node('I');

    // Build the tree structure
    head->left = A;
    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;
    C->left = tail;
    C->right = F;
    D->left = G;
    D->right = H;
    E->left = tail;
    E->right = tail;
    F->left = I;
    F->right = tail;
    G->left = tail;
    G->right = tail;
    H->left = tail;
    H->right = tail;
    I->left = tail;
    I->right = tail;

    // Perform preorder traversal and print the result
    printf("Pre-order Traverse result: ");
    preorder_traverse(head->left); // Start the traversal from the root node A
    printf("\n");

    printf("In-order Traverse result: ");
    inorder_traverse(head->left);
    printf("\n");

    printf("Post-order Travers result: ");
    postorder_traverse(head->left);
    printf("\n");

    printf("Level-order Travers result: ");
    levelorder_traverse(head->left);
    printf("\n");
}
