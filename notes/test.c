#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char my_array[5];
    *my_array = 'a';
    *(my_array+1) = 'b';
    my_array[2] = '\0';
    //printf("The code is %s.\n",my_array);

    char* aabb = malloc(sizeof(char)*3);
    *aabb = 'b';
    *(aabb+1) = 'c';
    *(aabb+2) = '\0';
    printf("Hi, %s\n",aabb);

    aabb = realloc(aabb,sizeof(char)*4);
    printf("Hi, %s\n",aabb);
    free(aabb);
}