#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 5;
    int* ptr = calloc(n,sizeof(int));
    int* ptr2 = malloc(n*sizeof(int));
    ptr = realloc(ptr,(n+1)*sizeof(int));
    free(ptr);
    free(ptr2);
}