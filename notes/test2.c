#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    int a;
};

int main(){
    struct Node newnode1;
    struct Node newnode2;
    newnode1.a = 1;
    newnode2.a = 2;

    if ( newnode1.a != newnode2.a ) printf("sus");

}