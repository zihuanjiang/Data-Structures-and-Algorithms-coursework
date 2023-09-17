#include <stdio.h>

int main(){
    int a[] ={1,2,3,4};
    *(a+1) = 5;

    for (int i = 0; i<4 ; i++){
        printf("%d ",a[i]);
    }
    
}