#include "a2.c"

int main(){
    char* ab = xor_encrypt('C');
    printf("%s\n",ab);

    int a = transfer_bit_to_int("1010000");
    printf("%d\n",a);

    char b = xor_decrypt(ab);
    printf("%c\n",b);

    char* my = "Program in C!";
    char* myy = transfer_msg_to_bit(my);
    printf("%s\n",myy);

}