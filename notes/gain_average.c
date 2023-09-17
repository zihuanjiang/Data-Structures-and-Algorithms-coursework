#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;    
};

float averageLinkedList(struct Node* L, int *n){
    if (L == NULL){
        return 0;
    }
    else{
        *n = *n +1;
        float gain_average = averageLinkedList(L->next,n);
        gain_average = (gain_average * (*n)) + L->data;
        gain_average = gain_average / (*n);
        return gain_average;
    }
}



int main(){
    struct Node* a = malloc(sizeof(struct Node));
    struct Node* b = malloc(sizeof(struct Node));
    struct Node* c = malloc(sizeof(struct Node));
    a->data = 5;
    b->data = 9;
    a->next = b;
    b->next = c;
    c->data = 13;
    c->next = NULL;
    int* n = malloc(sizeof(int));
    *n = 0;
    float ave;
    ave = averageLinkedList(a,n);
    printf("%f",ave);
    free(b);
    free(a);
    free(c);
}