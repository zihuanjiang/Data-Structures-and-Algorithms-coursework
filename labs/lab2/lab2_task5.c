#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p = (int *) malloc(sizeof(int));
    int *q = (int *) malloc(sizeof(int) * 2);
    *p = 1;
    *q = 10;
    
    // free(q)
    q = p;
    free(q);
    free(p);
}