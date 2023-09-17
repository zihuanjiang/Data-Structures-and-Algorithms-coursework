#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
    unsigned int i = 21;
    unsigned int right = i >> 2;
    unsigned int j = 56;
    printf("%d\n",right);
    printf("%d\n",i);
    printf("%d\n",i&j);
    printf("%d\n",(unsigned int)~i);
    printf("%d\n",i|j);
    printf("%d\n",i^j);
}