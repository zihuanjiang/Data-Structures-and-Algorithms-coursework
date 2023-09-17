#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    char* s = "HelloWorld";
    char* k = s+9;
    if (strcmp(k,"")==0) printf("hei\n");
    printf("%s+1\n",k);
    
    char* jh = "";
    printf("%lu",strlen(jh));
}