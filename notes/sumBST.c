#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* lChild;
    struct Node* rChild;    
};

int sumBST(struct Node* root){
    if (root == NULL){
        return 0;
    }
    int sum = 0;
    if (root->data > 10){
        sum = sum + root->data;
    }
    sum += sumBST(root->lChild);
    sum += sumBST(root->rChild);
    return sum;
}

int main(){
    struct Node* a = malloc(sizeof(struct Node));
    struct Node* b = malloc(sizeof(struct Node));
    struct Node* c = malloc(sizeof(struct Node));
    struct Node* d = malloc(sizeof(struct Node));
    struct Node* e = malloc(sizeof(struct Node));
    a->data = 19;
    b->data = 5;
    c->data = 2;
    d->data = 18;
    e->data = 20;
    a->lChild = b;
    a->rChild = e;
    e->lChild = NULL;
    e->rChild = NULL;
    b->lChild = c;
    b->rChild = d;
    c->lChild = NULL;
    c->rChild = NULL;
    d->lChild = NULL;
    d->rChild = NULL;
    int sum = sumBST(a);
    printf("%d",sum);
}