#include <stdio.h>
#include <stdlib.h>

void append(int** x, int* n, int val){
    *x = realloc(*x,(sizeof(int)) * (*n+1));
    *(*x+ *n) = val;
    *n = *n + 1;
}
