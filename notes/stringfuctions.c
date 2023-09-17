#include <string.h>
#include <stdio.h>

int main(){
    char a[] = "Ji Tang Lai Lo!";
    char b[25];

    strcpy(b,a);

    int length = strlen(b);
    for (int i=0; i<length; i++){
        printf("%c",b[i]);
    }

    char c[] = "abce";
    char d[] = "abce";
    int result = strcmp(c,d);
    printf("%d",result);

    return 0;
}